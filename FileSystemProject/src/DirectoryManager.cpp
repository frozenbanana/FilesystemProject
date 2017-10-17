#include "DirectoryManager.hpp"


Dnode::Dnode() {
	// This empty constructor should only be called for the rootNode
	this->data.inodePointer = nullptr;
	this->data.name = "root";
	this->data.dirPath = this->data.name;
	this->data.folder = true;
	this->parent = this;
	this->pfilesLinkedList = nullptr;
	this->pfoldersLinkedList = nullptr;
}
Dnode::Dnode(DnodeData data, Dnode* parent) {
	this->data.name = data.name;
	this->data.folder = data.folder;
	this->data.inodePointer = data.inodePointer;
	this->parent = parent;
}
Dnode::~Dnode() {

}

void Dnode::CleanFile() {
	// Give back the datablock to the datablockmanager.
	// Give back the Inode to the Inodemanager.
}

std::string Dnode::OutputData() {

	/*
	Praktiskt onödig.
	*/

	std::string returnData;
	returnData.append("\n");
	returnData.append("Dir-Path:   "), returnData.append(this->data.dirPath), returnData.append("\n");
	returnData.append("Name:       "), returnData.append(this->data.name), returnData.append("\n");
	returnData.append("Filetype:   ");

	if (this->data.folder == true)
		returnData.append("Directory. \n");
	else
		returnData.append("File. \n");

	returnData.append("\n");
	return returnData;
}

Dnode* Dnode::Step(std::string splitPath[], int depthLeft) {

	/*
	splitPath should be ordered last->first, so the path:
	root/firstfolder/secondfolder/file	should be:
	[0] = "file"
	[1] = "secondfolder"
	[2] = "firstfolder"
	[3] = "root"

	This way the remaining depth can easily be used to determine the
	current name we're looking for

	--
	The name we're currently looking for resides in splitPath[depthLeft - 1],
	since arrays go 0,1,2 and not 1,2,3.
	*/

	/*
	If the path starts with "." or ".." then proceeed from currentNode instead of rootNode
	however this function relies in rootNode so that decision is not made here, but
	in directoryManager.
	*/

	fileChildren* fileStepper = pfilesLinkedList;
	folderChildren* folderStepper = pfoldersLinkedList;

	// If we're still not deep enough, we can only go deeper through folders, so look at them
	if (depthLeft > 1) {	// 1 instead of 0 because we can access the layer below from the current node.

		/* Check the folders */
		if (folderStepper != nullptr) { // i contain atleast 1 folder

			// Is it the first one?
			if (folderStepper->me->data.name == splitPath[depthLeft - 2]) {	// '-2' because we're ignoring 'root' AND converting count->arr

				return folderStepper->me->Step(splitPath, (depthLeft - 1));
			}

			// Step through the rest of the folders and check'em
			while (folderStepper->next != nullptr) {
				folderStepper = folderStepper->next;

				if (folderStepper->me->data.name == splitPath[depthLeft - 2]) { // '-2' because we're ignoring 'root' AND converting count->arr
																				// Keep going down
					return folderStepper->me->Step(splitPath, (depthLeft - 1));
				}

			}

		}

		/* Check the folders */
		if (fileStepper != nullptr) { // i contain atleast 1 file

			// Is it the first one?
			if (fileStepper->me->data.name == splitPath[depthLeft - 2]) {	// '-2' because we're ignoring 'root' AND converting count->arr

				return fileStepper->me->Step(splitPath, (depthLeft - 1));
			}

			// Step through the rest of the folders and check'em
			while (fileStepper->next != nullptr) {
				fileStepper = fileStepper->next;

				if (fileStepper->me->data.name == splitPath[depthLeft - 2]) { // '-2' because we're ignoring 'root' AND converting count->arr
																				// Keep going down
					return fileStepper->me->Step(splitPath, (depthLeft - 1));
				}

			}

		}

	}
	/*  The file/folder we're looking for is one of the children */
	else {
		return this;
	}

}

void Dnode::AddNode(std::string fullpath, DnodeData data) {
	std::string dirPath = fullpath;

	// Is it a folder?
	if (data.folder == true) {
		folderChildren* pointer = this->pfoldersLinkedList;

		if (pointer == nullptr) {	// If this is the first folder in the linked list
			this->pfoldersLinkedList = new folderChildren;
			this->pfoldersLinkedList->me = new Dnode(data, this);
			this->pfoldersLinkedList->me->data.dirPath = dirPath;
		}
		else {						// If we need to step to the last folder in the list
			pointer = pointer->stepToLast();
			pointer->next = new folderChildren;
			pointer->next->me = new Dnode(data, this);
			pointer->next->me->data.dirPath = dirPath;
			pointer->next->previous = pointer;
		}

	} // Is it a file?
	else {
		fileChildren* pointer = this->pfilesLinkedList;

		if (pointer == nullptr) {	// If this is the first folder in the linked list
			this->pfilesLinkedList = new fileChildren;
			this->pfilesLinkedList->me = new Dnode(data, this);
			this->pfilesLinkedList->me->data.dirPath = dirPath;
		}
		else {
			pointer = pointer->stepToLast();
			pointer->next = new fileChildren;
			pointer->next->me = new Dnode(data, this);
			pointer->next->me->data.dirPath = dirPath;
			pointer->next->previous = pointer;
		}

	}

}

void Dnode::RemoveChildNode(std::string name) {
	
	fileChildren* fileStepper = this->pfilesLinkedList;
	folderChildren* folderStepper = this->pfoldersLinkedList;

	/* Is it a file we're looking for? */
	if (fileStepper != nullptr) { // I contain atleast 1 file

		do {

			if (fileStepper->me->data.name == name) {
				// Found it!
				// Since it's only a file, we only need to connect the previous and next

				if (fileStepper->next != nullptr) {	// We've got atleast one  ahead of us
					if (fileStepper->previous != nullptr) {		 // We're somewhere in the middle
						// Connect the left and right
						fileStepper->next->previous = fileStepper->previous;
						fileStepper->previous->next = fileStepper->next;
						
						delete fileStepper->me;
						delete fileStepper;
						fileStepper = nullptr;
						break;
					}
					else {										// We're the first one.
						// Connect base to the right
						fileStepper->next->previous = nullptr;
						this->pfilesLinkedList = fileStepper->next;
						
						delete fileStepper->me;
						delete fileStepper;
						break;
					}
				}
				else {		// We have nothing ahead of us.
					if (fileStepper->previous != nullptr) {		// We're the last one.
						// Tell the left its lost it's right
						fileStepper->previous->next = nullptr;

						delete fileStepper->me;
						delete fileStepper;
						break;
					}
					else {										// We're the ONLY one.
						delete this->pfilesLinkedList->me;
						delete this->pfilesLinkedList;
						this->pfilesLinkedList = nullptr;
						break;
					}

				}

			}
			fileStepper = fileStepper->next;

		} while (fileStepper != nullptr);
	}

	if (folderStepper != nullptr) {

		do {

			if (folderStepper->me->data.name == name) {
				// Found it!
				// Since it's only a file, we only need to connect the previous and next

				if (folderStepper->next != nullptr) {	// We've got atleast one  ahead of us
					if (folderStepper->previous != nullptr) {	 // We're somewhere in the middle
						// Connect the left and right
						folderStepper->next->previous = folderStepper->previous;
						folderStepper->previous->next = folderStepper->next;

						// Delete everything under this folder
						folderStepper->me->CleanDirectory();

						delete folderStepper->me;
						delete folderStepper;
						folderStepper = nullptr;
						break;
					}
					else {										// We're the first one.
						// Connect base to the right
						folderStepper->next->previous = nullptr;
						this->pfoldersLinkedList = folderStepper->next;

						// Delete everything under this folder
						folderStepper->me->CleanDirectory();

						delete folderStepper->me;
						delete folderStepper;
						break;
					}
				}
				else {		// We have nothing ahead of us.
					if (folderStepper->previous != nullptr) {		// We're the last one.
						// Tell the left its lost it's right
						folderStepper->previous->next = nullptr;

						// Delete everything under this folder
						folderStepper->me->CleanDirectory();

						delete folderStepper->me;
						delete folderStepper;
						break;
					}
					else {										// We're the ONLY one.
						// Delete everything under this folder
						folderStepper->me->CleanDirectory();

						delete this->pfoldersLinkedList->me;
						delete this->pfoldersLinkedList;
						this->pfoldersLinkedList = nullptr;
						break;
					}

				}

			}
			folderStepper = folderStepper->next;

		} while (folderStepper != nullptr);
	}


}


// Unoptimized
void Dnode::CleanDirectory() {
	/*
	The only concrete things we 'free up' is the dataBlocks and the Inodes,
	I.e. only the actual files need to be freed. This implementation steps through
	the entire directory, finds the files, and frees their nodes.
	This could be done way easier if this class had access to the first link in the
	"used i-nodes linked list".

	--
	I'd say the Directory's only purpose is being stepped through, via a filepath.
	It shouldn't have responsibility for creating or freeing Inodes/DataBlocks, it should
	only request them for the purpose of attaching to Dnodes.

	--
	So the All-Mighty-Clean function should reside in FileSystem, where it calls the
	InodeManager's CleanAll(), which recursively steps through the "used i-nodes linked list"
	where each link gives back the DataBlock to the Datablockmanager before returning to the
	"un-used i-nodes linked list"
	*/

	folderChildren* folderStepper = this->pfoldersLinkedList;
	fileChildren* fileStepper = this->pfilesLinkedList;

	/* Check if i contain more folders, if so, deal with them first */
	if (pfoldersLinkedList != nullptr) {	// i contain atleast one folder

											// Step to the last folder
		while (folderStepper->next != nullptr) {
			folderStepper = folderStepper->next;
		}
		// Call CleanAll() for all of the folders last->second.
		while (folderStepper->previous != nullptr) {
			folderStepper->me->CleanDirectory();
			folderStepper = folderStepper->previous;
		}
		folderStepper->me->CleanDirectory();	// Clean the first.

	}

	/* Clean up all the files i contain */
	if (pfilesLinkedList != nullptr) {	// i contain atleast 1 file

										// Step to the last file
		while (fileStepper->next != nullptr) {
			fileStepper = fileStepper->next;
		}
		// Call Clean for all of the files last->second.
		while (fileStepper->previous != nullptr) {
			fileStepper->me->CleanFile();
			fileStepper = fileStepper->previous;
		}
		fileStepper->me->CleanFile();	// Clean the first.

	}

	// On the way up, free up allocated structure
	if (this->pfoldersLinkedList != nullptr) {
		folderChildren* tempPointer1 = this->pfoldersLinkedList->stepToLast();
		folderChildren* tempPointer2;

		// Delete last->second
		while (tempPointer1->previous != nullptr) {
			tempPointer2 = tempPointer1->previous;
			delete tempPointer1->me;
			delete tempPointer1;
			tempPointer1 = tempPointer2;
		}
		// Delete first
		delete this->pfoldersLinkedList->me;
		delete this->pfoldersLinkedList;
		this->pfoldersLinkedList = nullptr;
	}
	if (this->pfilesLinkedList != nullptr) {
		fileChildren* tempPointer1 = this->pfilesLinkedList->stepToLast();
		fileChildren* tempPointer2;

		// Delete last->second
		while (tempPointer1->previous != nullptr) {
			tempPointer2 = tempPointer1->previous;
			delete tempPointer1->me;
			delete tempPointer1;
			tempPointer1 = tempPointer2;
		}
		// Delete first
		delete this->pfilesLinkedList->me;
		delete this->pfilesLinkedList;
		this->pfilesLinkedList = nullptr;
	}

}

//-----------------------------------------------------------
//						DIRECTORYMANAGER				   //
//-----------------------------------------------------------

DirectoryManager::DirectoryManager()
{
	// rootNode works itself out
	this->currentDirectory = &rootNode;

}
DirectoryManager::~DirectoryManager()
{
	/* Utgår nuvarande från att allt som inte sparas via spar-funktionen ska väck */
	this->CleanAll();
}

void DirectoryManager::CleanAll()
{
	this->rootNode.CleanDirectory();
}

std::string DirectoryManager::FetchCurrentDirInfo()
{
	std::string returnData = "\n";
	folderChildren *folderStepper = this->currentDirectory->pfoldersLinkedList;
	fileChildren *fileStepper = this->currentDirectory->pfilesLinkedList;


	if (this->currentDirectory != nullptr) {

		// Gather all the names of the folders
		if (folderStepper != nullptr) { // currentDir contains atleast 1 file

			returnData.append("Folders: \n");
			do {
				returnData.append("  "), returnData.append(folderStepper->me->data.name), returnData.append("\n");
				folderStepper = folderStepper->next;
			} while (folderStepper != nullptr);

			returnData.append("\n");
		}

		// Gather all the names of the files
		if (fileStepper != nullptr) {

			returnData.append("Files: \n");
			do {
				returnData.append("  "), returnData.append(fileStepper->me->data.name), returnData.append("\n");
				fileStepper = fileStepper->next;
			} while (fileStepper != nullptr);
			returnData.append("\n");


		}

	}
	else {
		returnData = "You've met with a terrible fate, haven't you?\n";
	}

	return returnData;
}

int DirectoryManager::CalculatePathLength(std::string entirePath)
{
	int pos = -1;
	int filePathSize = 1; // Always atleast "root" / "." / ".."

	while ((pos = entirePath.find("/", pos + 1)) != std::string::npos) {
		filePathSize++;
	}

	return filePathSize;
}

std::string DirectoryManager::SwitchCurrentDirectory(std::string directoryPath)
{
	int pathSize = this->CalculatePathLength(directoryPath);
	std::string *splitPath;
	this->SplitAPath(directoryPath, &splitPath);

	this->currentDirectory = this->StartStepping(splitPath, pathSize);
	
	return this->currentDirectory->data.dirPath;
}

void DirectoryManager::SplitAPath(std::string source, std::string* destination[]) {
	int oldPos = 0;
	int newPos = 0;
	std::string delimiter = "/";
	int pathLength = this->CalculatePathLength(source);
	int i = pathLength; // last->first so that it's formatted for stepping.

	if (pathLength > 1) {	// Bigger than ex: "root"

		*destination = new std::string[pathLength];

		//	oldPos = source.find('/', oldPos) + 1; // makes it ignore the first word
		while ((newPos = source.find('/', oldPos)) != std::string::npos) {
			// Cycles through the second first to second last
			(*destination)[i - 1] = source.substr(oldPos, newPos - oldPos); // -1 to convert count->array
			i--;
			oldPos = newPos + 1;
		} // makes it account for the last word
		(*destination)[i - 1] = source.substr(oldPos, newPos - oldPos);
	}
	else {
		*destination = new std::string[1];
		(*destination)[0] = source;
	}

}

Dnode* DirectoryManager::StartStepping(std::string splitPath[], int pathSize) {

	std::string outset = splitPath[pathSize - 1]; // splitPath is formatted first->last 0->n

	if (outset == "root") {
		return this->rootNode.Step(splitPath, pathSize);
	}
	else if (outset == ".") {
		return this->currentDirectory->Step(splitPath, pathSize);
	}
	else if (outset == "..") {
		return this->currentDirectory->parent->Step(splitPath, pathSize);
	}

}

void DirectoryManager::AddNode(std::string fullpath, DnodeData data) {
	// "root/folder1/NodeName" --> [NodeName][folder1][root]
	std::string *splitPathPlusName;
	int pathSize = this->CalculatePathLength(fullpath);
	this->SplitAPath(fullpath, &splitPathPlusName);
	data.name = splitPathPlusName[0];

	// [NodeName][folder1][root] --> [folder1][root]
	std::string *splitPathToParent = new std::string[pathSize - 1];
	for (int i = 0; i < pathSize - 1; i++) {
		splitPathToParent[i] = splitPathPlusName[i+1];
	}
	

	/* Is the node going to be added directly under 'root' or 'current'?*/
	if (pathSize == 2) { // "root/folder" is 2 size
		std::string outset = splitPathToParent[0];

		if (outset == "root") {
			this->rootNode.AddNode(fullpath, data);
		}
		else if (outset == ".") {
			this->currentDirectory->AddNode(fullpath, data);

		}
		else if (outset == "..") {
			this->currentDirectory->parent->AddNode(fullpath, data);
		}

	}
	else {
		Dnode* parent = this->StartStepping(splitPathToParent, pathSize-1); // "root" is 1 size

		if (parent == nullptr) {
		}
		else {
			if (parent->data.folder == true)
				parent->AddNode(fullpath, data);
		}
	}

	// Free up used memory
	delete[] splitPathPlusName;
	delete[] splitPathToParent;
}

void DirectoryManager::RemoveNode(std::string fullpath) {
	// "root/folder1/NodeName" --> [NodeName][folder1][root]
	std::string *splitPathPlusName;
	int pathSize = this->CalculatePathLength(fullpath);
	this->SplitAPath(fullpath, &splitPathPlusName);

	// [NodeName][folder1][root] --> [root][folder1]
	std::string *splitPathToParent = new std::string[pathSize - 1];
	for (int i = 0; i < pathSize - 1; i++) {
		splitPathToParent[i] = splitPathPlusName[i + 1];
	}

	/* Is the node going to be added directly under 'root' or 'current'?*/
	if (pathSize <= 2) { // "root/folder" is 2 size
		std::string outset = splitPathToParent[0];

		if (outset == "root") {
			this->rootNode.RemoveChildNode(splitPathPlusName[0]);
		}
		else if (outset == ".") {
			this->currentDirectory->RemoveChildNode(splitPathPlusName[0]);

		}
		else if (outset == "..") {
			this->currentDirectory->parent->RemoveChildNode(splitPathPlusName[0]);
		}

	}
	else {
		Dnode* parent = this->StartStepping(splitPathToParent, pathSize - 1); // "root" is 1 size

		if (parent != nullptr) {
			if (parent->data.folder == true)
				parent->RemoveChildNode(splitPathPlusName[0]);
		}
		else {
			
		}
	}

	delete[] splitPathPlusName;
	delete[] splitPathToParent;
}