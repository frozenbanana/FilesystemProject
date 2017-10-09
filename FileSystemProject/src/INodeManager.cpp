#include "INodeManager.h"





INode_Handle::INode_Handle()
{
  m_underneath = nullptr;
}

INode_Handle::~INode_Handle()
{

}





INodeManager::INodeManager()
{
  m_FreeINodeCount = INODE_COUNT;   // Total number of INode free shells (also number of INodes)

  INode_Handle *temp_FreeHandle;             // Temp INodeHandle for below for-loop

  m_stackTop = new INode_Handle;

  for (int i = 0; i < INODE_COUNT; i++)
  {
    temp_FreeHandle = new INode_Handle;
    temp_FreeHandle->m_underneath = m_stackTop;
    m_stackTop = temp_FreeHandle;
  }
}
