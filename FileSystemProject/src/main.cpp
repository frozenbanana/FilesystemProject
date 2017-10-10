#include <iostream>
#include <stdio.h>
#include <string>
#include <crtdbg.h>

#include "INodeManager.h"
#include "INode.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	INodeManager *myManager;
	myManager = new INodeManager;

	int tester;

	std::cin >> tester;
	std::cout << tester;
	std::cin >> tester;
	std::cout << tester;

	delete myManager;

	return 0;
}