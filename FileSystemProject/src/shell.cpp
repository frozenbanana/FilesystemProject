#include <iostream>
#include <sstream>
#include "FileSystem.hpp"
#include <crtdbg.h>

/*



*/


const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
	"quit","format","ls","create","cat","createImage","restoreImage",
	"rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
bool quit();
std::string help();

/* More functions ... */

int main(void) {
	// ------------------- Vårt -------------------
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	FileSystem system;

	std::string thatsCheating;
	std::string fileData;

	// ------------------- Vårt -------------------


	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "Pr0n@DV1337";    // Change this if you want another user to be displayed

	std::string currentDir = "root";	// current directory, used for output

	bool bRun = true;

	do {
		std::cout << user << ":" << currentDir << "$ ";
		getline(std::cin, userCommand);

		int nrOfCommands = parseCommandString(userCommand, commandArr);

		if (nrOfCommands > 1) { // Forces "/" to become "root/"

			if (commandArr[1].at(0) != '/') { 
				thatsCheating = "";
				thatsCheating.append(currentDir);
				thatsCheating.append("/");
				thatsCheating.append(commandArr[1]);
				commandArr[1] = thatsCheating;
			}
			if (nrOfCommands > 2) {
				if (commandArr[2].at(0) != '/') {
					thatsCheating = "";
					thatsCheating.append(currentDir);
					thatsCheating.append("/");
					thatsCheating.append(commandArr[2]);
					commandArr[2] = thatsCheating;
				}
			}
		}
		

		if (nrOfCommands > 0) {

			int cIndex = findCommand(commandArr[0]);
			switch (cIndex) {

			case 0: { //quit
				bRun = quit();
				break;
			}
			case 1: { // format
				std::cout << "Formatting virtual disk...\n" << std::endl;
				system.Format();
				std::cout << "Done!\n" << std::endl;
				break;
			}
			case 2: { // ls
				std::cout << system.ls();
				break;
			}
			case 3: { // create 
				std::cout << "Enter filedata: \n" << std::endl;
				getline(std::cin, fileData);
				system.Create(commandArr[1], fileData);
				break;
			}				
			case 4: {  // cat
				std::cout << system.cat(commandArr[1]) << std::endl;
				break;
			}
			case 5: { // createImage
				system.CreateImage();
				break;
			}
			case 6: { // restoreImage
				system.RestoreImage();
				break;
			}
			case 7: { // rm
				system.Remove(commandArr[1]);
				break;
			}
			case 8: { // cp
				system.Copy(commandArr[1], commandArr[2]);
				break;
			}
			case 9: { // append
				// EJ NÖDVÄNDIG
				break;
			}
			case 10: { // mv
				// EJ NÖDVÄNDIG
				break;
			}
			case 11: { // mkdir
				system.MakeDirectory(commandArr[1]);
				break;
			}
			case 12: { // cd
				currentDir = system.cd(commandArr[1]);
				break;
			}
			case 13: { // pwd
				std::cout << system.pwd(commandArr[1]);
				break;
			}
			case 14: { // help
				std::cout << help() << std::endl;
				break;
			}

			default:
				std::cout << "Unknown command: " << commandArr[0] << std::endl;
			}
		}
	} while (bRun == true);

	return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
	std::stringstream ssin(userCommand);
	int counter = 0;
	while (ssin.good() && counter < MAXCOMMANDS) {
		ssin >> strArr[counter];
		counter++;
	}
	if (strArr[0] == "") {
		counter = 0;
	}
	return counter;
}
int findCommand(std::string &command) {
	int index = -1;
	for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
		if (command == availableCommands[i]) {
			index = i;
		}
	}
	return index;
}

bool quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string help() {
	std::string helpStr;
	helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
	helpStr += "-----------------------------------------------------------------------------------\n";
	helpStr += "* quit:                             Quit OSD Disk Tool\n";
	helpStr += "* format;                           Formats disk\n";
	helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
	helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
	helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
	helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
	helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
	helpStr += "* rm     <file>:                    Removes <file>\n";
	helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
	helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
	helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
	helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
	helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
	helpStr += "* pwd:                              Get current working directory\n";
	helpStr += "* help:                             Prints this help screen\n";
	return helpStr;
}