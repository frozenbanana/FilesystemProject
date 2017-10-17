#include "FileSystem.hpp"
#include <fstream>

FileSystem::FileSystem() {

}
FileSystem::~FileSystem() {

}

void FileSystem::Initialize() {



	// DirectoryManager's constructor solves itself.
}
void FileSystem::CleanAll() {
	// Do things according to InodeManager
	// Do things according to DataBlockManager

	m_DirectoryManager.CleanAll();
}


// --------- Shell-Called Functions ---------//
//											 //
// --------- Shell-Called Functions ---------//

// +-+-+-+-+ Creating & Deleting folders/files +-+-+-+-+
void FileSystem::Create(std::string fullpath, std::string fileData) {
	/* Fetch Datablock from DatablockManager */
	int datablockID; // = m_DatablockManager.RequestDatablock();

	/* Fetch Inode from InodeManager */
	INode* InodePointer = m_InodeManager.PopFreeINode();

	/* Attach Datablock to InodePointer */
	this->m_DatablockManager.JoinBlocksToINode(InodePointer, fileData.size());

	/* Attach fileData to the InodePointer */

	// Parse fileData according to ELEMENTSPERBLOCK
	int length = fileData.length();

	int blockCount = ((ELEMENTSPERBLOCK-1 + length) / ELEMENTSPERBLOCK);
	char** doubleArray = new char*[length];

	BlockHandle* stepper = &InodePointer->m_rootHandle;
	
	if (blockCount > 1) {

		// Handle the first->secondlast blocks normally.
		for (int i = 0; i < blockCount - 1; i++) {
			doubleArray[i] = new char[ELEMENTSPERBLOCK];

			// Per character inside a block
			for (int j = 0; j < ELEMENTSPERBLOCK; j++) {
				//temp = fileData.at(i * j);
				doubleArray[i][j] = fileData.at((i*ELEMENTSPERBLOCK) + j);
			}

			stepper->GetBlock()->writeBlock(doubleArray[i], ELEMENTSPERBLOCK);
			stepper = stepper->m_nextHandle;
		}

		// Handle the last block specifically, since we don't want to write 512 chars here
		doubleArray[blockCount - 1] = new char[ELEMENTSPERBLOCK];
		fileData = fileData.substr(((blockCount - 1)*ELEMENTSPERBLOCK), std::string::npos);
		length = fileData.length();

		for (int i = 0; i < length; i++) {

			doubleArray[blockCount - 1][i] = fileData.at(i);
		}

		stepper->GetBlock()->writeBlock(doubleArray[blockCount - 1], length);
		
				
	}
	else {
		// Handle the only block specifically, since we don't want to write 512 chars here
		doubleArray[0] = new char[ELEMENTSPERBLOCK];
		fileData = fileData.substr(((blockCount - 1)*ELEMENTSPERBLOCK), std::string::npos);
		length = fileData.length();
		for (int i = 0; i < length; i++) {

			doubleArray[0][i] = fileData.at(i);
		}
		
		stepper->GetBlock()->writeBlock(doubleArray[0], length);
	}


	/* Attach the Inodepointer to a Dnode */
	DnodeData data;
	data.folder = false;
	data.inodePointer = InodePointer;

	/* Attatch the node to the Directory-Tree */
	m_DirectoryManager.AddNode(fullpath, data);

	// Clean up
	for (int i = 0; i < blockCount; i++) {
		delete[] doubleArray[i];
	}
	delete[] doubleArray;
}
void FileSystem::MakeDirectory(std::string fullpath) {
	/* Fetch Inode from InodeManager */
	INode InodePointer; // [*] = m_InodeManager.RequestInode();
	// InodePointer->DatablockID = -1;

	/* Attach this information to a Dnode */
	DnodeData data;
	data.folder = true;
	data.inodePointer = &InodePointer;

	/* Attach the node to the Directory-Tree */
	m_DirectoryManager.AddNode(fullpath, data);
}
void FileSystem::Copy(std::string originalFilePath, std::string newFilePath) {
	
	// Fetch the original Inode
	int pathSize = this->m_DirectoryManager.CalculatePathLength(originalFilePath);
	std::string *originalSplitPath;
	this->m_DirectoryManager.SplitAPath(originalFilePath, &originalSplitPath);
	INode* oldINodePointer = this->m_DirectoryManager.StartStepping(originalSplitPath, pathSize)->data.inodePointer;;

	// Ask for array of Datablocks
	Block* *newBlockArray;
	int triangleSize = oldINodePointer->GetSize();
	this->m_DatablockManager.CopyBlocks(&oldINodePointer->m_rootHandle, triangleSize, &newBlockArray);

	// Request a new Inode
	INode* newINodePointer = this->m_InodeManager.PopFreeINode();

	// Attach the given array to the new Inode
	newINodePointer->InsertBlocks(newBlockArray, triangleSize);

	// Attach Inode to a Dnode
	DnodeData data;
	data.inodePointer = newINodePointer;
	data.folder = false;
	this->m_DirectoryManager.AddNode(newFilePath, data);

	delete[] newBlockArray;
	delete[] originalSplitPath;
}
void FileSystem::Remove(std::string filePath) {
	m_DirectoryManager.RemoveNode(filePath);
}
// +-+-+-+-+ Restart & Quit +-+-+-+-+
void FileSystem::Format() {
	this->CleanAll();
}
void FileSystem::Quit() {
	this->CleanAll();
}
// +-+-+-+-+ Saving & Loading +-+-+-+-+
void FileSystem::CreateImage() {
	std::ofstream saveFileSize_fs("sizeOfObject.ros");
	if (saveFileSize_fs.is_open())
	{	
		saveFileSize_fs << sizeof(*this);
		saveFileSize_fs.close();
	}

	std::ofstream object_fs("savedFilesystem.ros", std::ios::binary);
	object_fs.write((char *)this, sizeof(this));
	if (object_fs.is_open())
		object_fs.close();
}

void FileSystem::RestoreImage() {
	std::ifstream getSizeFile_fs;
	int sizeOfObject = 0;

	getSizeFile_fs.open("sizeOfObject.ros");
	if (getSizeFile_fs.is_open())
	{
		getSizeFile_fs >> sizeOfObject;

		getSizeFile_fs.close();

		std::ifstream object_fs("sizeOfObject.ros", std::ios::binary);

		if (object_fs.is_open())
		{
			object_fs.read((char *)this, sizeOfObject);
			if (object_fs.is_open())
				object_fs.close();
		}
	}

	else
	{
		std::cout << "Daniel does not like this. But this error check means that something is wrong with the filepath of getSizeFile. How helpful (if we actually used it)!" << std::endl;
	}
}

// +-+-+-+-+ Output +-+-+-+-+
std::string FileSystem::cat(std::string filePath) {
	std::string *splitPath;
	int length = m_DirectoryManager.CalculatePathLength(filePath);
	m_DirectoryManager.SplitAPath(filePath, &splitPath);

	Dnode* DnodePointer = m_DirectoryManager.StartStepping(splitPath, length);
	BlockHandle* stepper = &DnodePointer->data.inodePointer->m_rootHandle;
	std::string returnData;
	returnData.append("\n");
	while (stepper != nullptr) {
		std::string temp = stepper->GetBlock()->toString();
		returnData.append(temp);
		stepper = stepper->m_nextHandle;
	}
	returnData.append("\n");
	
	delete[] splitPath;
	return returnData;
}
std::string FileSystem::pwd(std::string filePath) {
	std::string returnData;

	returnData.append("\n");
	returnData.append(this->m_DirectoryManager.currentDirectory->data.dirPath);
	returnData.append("\n\n");

	return returnData;
}

// +-+-+-+-+ CurrentDir +-+-+-+-+
std::string FileSystem::ls() {
	return m_DirectoryManager.FetchCurrentDirInfo();
}
std::string FileSystem::cd(std::string filePath) {
	return m_DirectoryManager.SwitchCurrentDirectory(filePath);
}