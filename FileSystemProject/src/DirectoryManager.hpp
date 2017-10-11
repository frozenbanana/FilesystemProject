#ifndef DIRECTORYMANAGER_HPP
#define DIRECTORYMANAGER_HPP

#include <string>

/*


Fixa Dnode::AddNode() så att den lägger till dirPath i Children's me.data.dirPath;


*/

class Dnode;	// Forward deklarerad pga file/folder-Children

struct Inode {
	int sampledata;
};

struct DnodeData { // The data for a Dnode, so that creating one is easier.
	std::string name;
	std::string dirPath;
	bool folder = false;
	Inode* inodePointer = nullptr;
};

struct fileChildren { // Linked list of all the files in a folder
	Dnode* me = nullptr;
	fileChildren* next = nullptr;
	fileChildren* previous = nullptr;


	fileChildren* stepToLast() {
		if (this->next != nullptr)
			return this->next->stepToLast();
		else
			return this;
	}
};

struct folderChildren { // Linked list of all the folders in a folder
	Dnode* me = nullptr;
	folderChildren* next = nullptr;
	folderChildren* previous = nullptr;


	folderChildren* stepToLast() {
		if (this->next != nullptr)
			return this->next->stepToLast();
		else
			return this;
	}
};

class Dnode {
public:
	DnodeData data;
	Dnode* parent = nullptr;
	folderChildren* pfoldersLinkedList = nullptr;
	fileChildren* pfilesLinkedList = nullptr;


	// ---- Functions ----
	Dnode();
	Dnode(DnodeData data, Dnode* parent);
	~Dnode();

	std::string OutputData();

	// Either returns the Dnode related to the path, or a nullptr if it doesn't exist.
	Dnode* Step(std::string splitPath[], int pathSize);

	void AddNode(std::string fullpath, DnodeData data);
	void RemoveChildNode(std::string name);

	void CleanFile();
	void CleanDirectory();

};


class DirectoryManager {
private:

public:
	Dnode rootNode;
	Dnode* currentDirectory;	// The directory the user is currently looking at.

	DirectoryManager();
	~DirectoryManager();
	void CleanAll();

	std::string FetchCurrentDirInfo();
	std::string SwitchCurrentDirectory(std::string directoryPath);

	int CalculatePathLength(std::string entirePath);
	void SplitAPath(std::string source, std::string* AdrOfArr_destination[]);

	Dnode* StartStepping(std::string splitPath[], int pathSize);

	//
	void AddNode(std::string fullpath, DnodeData data);
	void RemoveNode(std::string fullpath);



};

#endif