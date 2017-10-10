#ifndef INODE_MANAGER_H
#define INODE_MANAGER_H


#include <string>
#include <iostream>
#include <stdio.h>
#include "INode.h"

#define INODE_COUNT 250


class INodeManager
{
private:
	INode		m_INodeList[INODE_COUNT];		// Static list of ALL INodes

	int			m_FreeINodeCount = INODE_COUNT;	// Current # of free INodes
	INode*		m_FreeINodeList[INODE_COUNT];	// Static list of all FREE INodes

    public:
		INodeManager();
		~INodeManager();

		/* - - - - - FUNCTION COMMENTS - - - - -
		 • 'Pops' and returns the address to a free INode
		 • RETURN VALUE: 0 free INodes = nullptr, else address
		*/
		INode*		PopFreeINode();

		/* - - - - - FUNCTION COMMENTS - - - - -
		 • 'Pushes' a free INode back into the 'FreeINodeList'
		 • RETURN VALUE: 'true' if successful, else 'false'
		*/
		bool		PushFreeINode(INode* INode_in);
};

#endif