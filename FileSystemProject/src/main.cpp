#include <iostream>
#include <stdio.h>
#include <string>

#include "INodeManager.h"
#include "INode.h"
#include "memblockdevice.h"


int main()
{

    std::cout << "Testing starting" << std::endl;
    MemBlockDevice memBD;    
    INodeManager inodeMan;
    memBD.JoinBlocksToINode(inodeMan.PopFreeINode(), 40);
    std::cout << "Testing finished" << std::endl;
    return 0;
}
