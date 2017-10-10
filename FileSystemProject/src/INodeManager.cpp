#include "INodeManager.h"


INodeManager::INodeManager()
{
	for (int i = 0; i < INODE_COUNT; i++)
		m_FreeINodeList[i] = &(m_INodeList[i]);
}

INodeManager::~INodeManager()
{

}



// PUBLIC FUNCTIONS

INode* INodeManager::PopFreeINode()
{
	INode*	tempINodeHolder = nullptr;	// Will temp. hold addr. to popped INode
	int		tempArraySlot = (m_FreeINodeCount - 1);

	if (tempArraySlot >= 0 && tempArraySlot < 250)
	{
		tempINodeHolder = m_FreeINodeList[tempArraySlot];	// INode moved to temp
		m_FreeINodeList[tempArraySlot] = nullptr;	// 'Deleting' INode from 'free'-list

		m_FreeINodeCount--;	// Updating FreeINodeCount (1 INode removed, --)
	}

	return tempINodeHolder;
}

bool INodeManager::PushFreeINode(INode* INode_in)
{
	bool returnValue = false; // Return value (false = default = unsuccessful)
	int tempArraySlot = m_FreeINodeCount;

	if (tempArraySlot >= 0 && tempArraySlot < 250)
	{
		m_FreeINodeList[tempArraySlot] = INode_in;	// Earliest free slot now occupied
		m_FreeINodeCount++;	// Updating FreeINodeCount (1 INode added, ++)

		returnValue = true;
	}

	return returnValue;
}