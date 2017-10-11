#include "FileSystem.hpp"


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
void FileSystem::Create(std::string fullpath /* Also needs the raw file-data*/) {
	/* Fetch Datablock from DatablockManager */
	int datablockID; // = m_DatablockManager.RequestDatablock();

	/* Fetch Inode from InodeManager */
	Inode InodePointer; // [*]  = m_InodeManager.RequestInode();
	// InodePointer->DatablockID = dataBlockID;

	/* Attach this information to a Dnode */
	DnodeData data;
	data.folder = false;
	data.inodePointer = &InodePointer;

	/* Attatch the node to the Directory-Tree */
	m_DirectoryManager.AddNode(fullpath, data);
}
void FileSystem::MakeDirectory(std::string fullpath) {
	/* Fetch Inode from InodeManager */
	Inode InodePointer; // [*] = m_InodeManager.RequestInode();
	// InodePointer->DatablockID = -1;

	/* Attach this information to a Dnode */
	DnodeData data;
	data.folder = true;
	data.inodePointer = &InodePointer;

	/* Attatch the node to the Directory-Tree */
	m_DirectoryManager.AddNode(fullpath, data);
}
void FileSystem::Copy(std::string originalFilePath, std::string newFilePath) {
	// Read
	// node* = Tillgång till inode via originalfilepath

	// Write
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

}
void FileSystem::RestoreImage() {

}
// +-+-+-+-+ Output +-+-+-+-+
std::string FileSystem::cat(std::string filePath) {
	std::string *splitPath;
	int length = m_DirectoryManager.CalculatePathLength(filePath);
	m_DirectoryManager.SplitAPath(filePath, &splitPath);

	return m_DirectoryManager.StartStepping(splitPath, length)->OutputData();
}
std::string FileSystem::pwd(std::string filePath) {
	std::string returnData;

	return returnData;
}
// +-+-+-+-+ CurrentDir +-+-+-+-+
std::string FileSystem::ls() {
	return m_DirectoryManager.FetchCurrentDirInfo();
}
std::string FileSystem::cd(std::string filePath) {
	return m_DirectoryManager.SwitchCurrentDirectory(filePath);
}