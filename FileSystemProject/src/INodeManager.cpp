#include "INodeManager.h"


// PRIVATE FUNCTIONS

void INodeManager::cleanINodeStack()
{
	for (int i = 0; i < INODE_COUNT; i++)
	{
		
	}
}


INodeManager::INodeManager()
{
	INode*		temp_INodePointers[INODE_COUNT];

  for (int i = 0; i < INODE_COUNT; i++)
  {
	  temp_INodePointers[i] = new INode;
	  m_freeINodeStack.push(temp_INodePointers[i]);
  }
}

INodeManager::~INodeManager()
{
	INode*		temp_INodePointer;

	for (int i = 0; i < INODE_COUNT; i++)
	{
		temp_INodePointer = m_freeINodeStack.pop(); // Currently the problem, need to rethink
	}
}
