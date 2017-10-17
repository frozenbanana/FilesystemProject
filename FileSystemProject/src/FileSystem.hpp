#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "DirectoryManager.hpp"
#include "INodeManager.h"
#include "memblockdevice.h"
#include "block.h"


class FileSystem {
private:
	DirectoryManager m_DirectoryManager;
	INodeManager	 m_InodeManager;
	MemBlockDevice	 m_DatablockManager;


public:
	FileSystem();
	~FileSystem();

	void Initialize();
	void CleanAll();


	
	// --------- Shell-Called Functions ---------
	// Creating & Deleting folders/files
	void Create(std::string fullpath, std::string fileData);
	void MakeDirectory(std::string fullpath);
	void Copy(std::string originalFilePath, std::string newFilePath);
	void Remove(std::string filePath);
	// Restart & Quit
	void Format();
	void Quit();
	// Saving & Loading
	void CreateImage();
	void RestoreImage();
	// Output
	std::string cat(std::string filePath);
	std::string pwd(std::string filePath);
	// CurrentDir
	std::string ls();
	std::string cd(std::string filePath);
	
};




#endif