#ifndef INODE_MANAGER_H
#define INODE_MANAGER_H


#include <string>
#include <iostream>
#include <stack>
#include <stdio.h>
#include "INode.h"

#define INODE_COUNT 250


class INodeManager
{
    private:
		int					m_FreeINodeCount;
		std::stack<INode*>	m_freeINodeStack;

		void				cleanINodeStack();

    public:  
		INodeManager();
		~INodeManager();
};

#endif