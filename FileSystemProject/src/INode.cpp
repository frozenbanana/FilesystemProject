#include "INode.h"


// PUBLIC FUNCTIONS

BlockHandle::BlockHandle()
{
  m_thisBlock = nullptr;
  m_nextHandle = nullptr;
}

BlockHandle::~BlockHandle()
{

}

Block* BlockHandle::GetBlock()
{
	return m_thisBlock;
}

void BlockHandle::SetBlock(Block* dataBlock_in)
{
	m_thisBlock = dataBlock_in;
}



///////////////////////////////////////////////////////////////////////////////////////////////




// PRIVATE FUNCTIONS

/*- - - - - FUNCTION COMMENTS - - - - -
Makes use of two clean functions
 • CleanAll() gives initial access to root
 • CleanNextHandle() recursively deletes all past root*/
void INode::CleanAll()
{
	if (m_rootHandle.m_nextHandle != nullptr)
		CleanNextHandle(m_rootHandle.m_nextHandle);

	// No 'delete' due to static root
}

/*- - - - FUNCTION COMMENTS - - - - -
See 'Function Comments' for 'CleanAll() function*/
void INode::CleanNextHandle(BlockHandle *BlockHandle_in)
{
  if (BlockHandle_in->m_nextHandle != nullptr)
	  CleanNextHandle(BlockHandle_in->m_nextHandle);  // Recursive func. call

  delete BlockHandle_in;	// Deleting self AFTER having called recursion
}								


void INode::ExtendList(BlockHandle* rootHandle_in, int blockCount_in)
{
  BlockHandle *tempHandle = rootHandle_in;  // Initially set to rootHandle (necc. for both cases below)

  if (tempHandle->GetBlock() != nullptr) // Safety net in case we're adding MORE blocks
  {
    while (tempHandle->m_nextHandle != nullptr) // Stepping through existing handles
      tempHandle = tempHandle->m_nextHandle;
  
    for (int i = 0; i < blockCount_in; i++) // Extension may begin here (see above 2 comments)
    {
      tempHandle->m_nextHandle = new BlockHandle;
      tempHandle = tempHandle->m_nextHandle;
    }
  }

  else  // rootHandle is empty = standard proceeding
  {
    for (int i = 0; i < (blockCount_in - 1); i++)
    {
      tempHandle->m_nextHandle = new BlockHandle;
      tempHandle = tempHandle->m_nextHandle;
    }
  }
}


void INode::InsertList(BlockHandle* rootHandle_in, Block* *BlockArray_in, int BlockCount_in)
{
   BlockHandle *tempHandle = rootHandle_in;

   int         blocksLeft = BlockCount_in;
   int         currentArraySlot = 0;  // Not necessary, but increases clarity

   if (tempHandle->GetBlock() != nullptr) // rootHandle already contains data!!
   {
     tempHandle = tempHandle->m_nextHandle;

     while (tempHandle->GetBlock() != nullptr) // Stepping till handle with empty Block
       tempHandle = tempHandle->m_nextHandle;
   }

   else // rootHandle contained no data = fill root, then proceed
   {
     tempHandle->SetBlock(BlockArray_in[currentArraySlot]);
     currentArraySlot++;
     blocksLeft--;

     tempHandle->m_nextHandle;
   }

   while (blocksLeft > 0)
   {
     tempHandle->SetBlock(BlockArray_in[currentArraySlot]);
     currentArraySlot++;
     blocksLeft--; 
   }
}





// PUBLIC FUNCTIONS

INode::INode()
{
  m_isDirectory = false;

  for (int i = 0; i < 10; i++)
    m_permissionData[i] = 0;
}

INode::INode(bool isDirectory_in, bool *permissionData_in)
{
  m_isDirectory = isDirectory_in;
  
  for (int i = 0; i < 10; i++)
    m_permissionData[i] = permissionData_in[i];
}

INode::~INode()
{
  CleanAll(); 
}


bool INode::InsertBlocks(Block* *BlockArray_in, int BlockCount_in)
{
    // Return Bool to check success
	BlockHandle *tempHandle;
  bool        booleanReturnValue = true;

  ExtendList(&m_rootHandle, BlockCount_in);
  
  InsertList(&m_rootHandle, BlockArray_in, BlockCount_in);

	return booleanReturnValue;
}
