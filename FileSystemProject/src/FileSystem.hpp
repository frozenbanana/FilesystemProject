#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "DirectoryManager.hpp"
// include InodeManager
// include DatablockManager
// include Formattor

class FileSystem {
private:
	DirectoryManager m_DirectoryManager;
//	InodeManager	 m_InodeManager;
//	DatablockManager m_DatablockManager;
//	Formattor		 m_OutputFormattor;


public:
	FileSystem();
	~FileSystem();

	void Initialize();
	void CleanAll();










	
	// --------- Shell-Called Functions ---------
	// Creating & Deleting folders/files
	void Create(std::string fullpath);
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