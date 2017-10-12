#include "memblockdevice.h"
#include <stdexcept>
#include <math.h>

MemBlockDevice::MemBlockDevice(int nrOfBlocks): BlockDevice(nrOfBlocks)
{
  memBlocks = new Block[nrOfBlocks];
  for(int i = 0; i < nrOfBlocks; i++){ m_FreeBlocksIndex.push_back(i); }
}
     
MemBlockDevice::MemBlockDevice(const MemBlockDevice &other) : BlockDevice(other) 
{
  m_FreeBlocksIndex.clear();
  m_FreeBlocksIndex = other.m_FreeBlocksIndex; 
}

MemBlockDevice::~MemBlockDevice() {
    m_FreeBlocksIndex.clear();
    Destroy();
    /* Implicit call to base-class destructor */
}

MemBlockDevice& MemBlockDevice::operator=(const MemBlockDevice &other) 
{
    delete [] this->memBlocks;
    this->nrOfBlocks = other.nrOfBlocks;
    this->m_freeSpaceStart = other.m_freeSpaceStart;
    this->memBlocks = new Block[this->nrOfBlocks];

    for (int i = 0; i < this->nrOfBlocks; ++i)
        this->memBlocks[i] = other.memBlocks[i];

    return *this;
}

Block& MemBlockDevice::operator[](int index) const 
{
    if (index < 0 || index >= this->nrOfBlocks) {
        throw std::out_of_range("Illegal access\n");
    }
    else {
        return this->memBlocks[index];
    }
}

int MemBlockDevice::spaceLeft() const 
{
    return m_FreeBlocksIndex.size() * memBlocks[0].size();
}

int MemBlockDevice::writeBlock(int blockNr, const std::vector<char> &vec) {
    int output = -1;    // Assume blockNr out-of-range

    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        /* -2 = vec and block dont have same dimensions */
        /* 1 = success */
        output = this->memBlocks[blockNr].writeBlock(vec);
    }
    return output;
}

int MemBlockDevice::writeBlock(int blockNr, const std::string &strBlock) 
{
    int output = -1;    // Assume blockNr out-of-range

    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        /* -2 = str-length and block dont have same dimensions */
        /* 1 = success */
        output = this->memBlocks[blockNr].writeBlock(strBlock);
    }
    return output;
}

int MemBlockDevice::writeBlock(int blockNr, const char cArr[]) 
{
    int output = -1;    // Assume blockNr out-of-range
    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        output = 1;
        // Underlying function writeBlock cannot check array-dimension.
        this->memBlocks[blockNr].writeBlock(cArr);
    }
    return output;
}

Block MemBlockDevice::readBlock(int blockNr) const {
    if (blockNr < 0 || blockNr >= this->nrOfBlocks)
        throw std::out_of_range("Block out of range");
    else {
        Block a(this->memBlocks[blockNr]);
        return a;
    }
}

/* Resets all the blocks */
void MemBlockDevice::reset() {
    for (int i = 0; i < this->nrOfBlocks; ++i) {
        this->memBlocks[i].reset('0');
    }
}

int MemBlockDevice::size() const {
    return this->nrOfBlocks;
}

void MemBlockDevice::ReclaimBlock(int blockIndex)
{ 
  m_FreeBlocksIndex.push_back(blockIndex);
}

bool MemBlockDevice::JoinBlocksToINode(INode* node, int fileSize)
{ 
  bool flag = false;
  int amountOfBlocksNeeded = int(ceil(fileSize / memBlocks[0].size()));
  Block** blocksToAttach = new Block*[amountOfBlocksNeeded];

  if( m_FreeBlocksIndex.size() < amountOfBlocksNeeded ) 
    return flag;
  
  // Join block to INode 
  for(int i = 0; i < amountOfBlocksNeeded; i++)
  {
      int blockAddress = m_FreeBlocksIndex.back();
      m_FreeBlocksIndex.pop_back();
      blocksToAttach[i] = &(memBlocks[blockAddress]);
  } 

  node->InsertBlocks(blocksToAttach, amountOfBlocksNeeded); 
  delete [] blocksToAttach;
  return flag;

}

void MemBlockDevice::Clean()
{
    m_FreeBlocksIndex.clear();
    for(int i = 0; i < nrOfBlocks; i++)
        m_FreeBlocksIndex.push_back(i);
}


void MemBlockDevice::Destroy()
{
    delete [] memBlocks;
}


