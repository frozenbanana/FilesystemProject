#include "INode.h"

DataBlockHandle::DataBlockHandle()
{
  m_thisDataBlock = nullptr;
  m_nextDataHandle = nullptr;
}

DataBlockHandle::~DataBlockHandle()
{

}




// PRIVATE FUNCTIONS

void INode::cleanINode(DataBlockHandle *DataBlockHandle_in)
{
  if (DataBlockHandle_in->m_nextDataHandle != nullptr)
    m_cleanINode(m_nextDataHandle);

  delete DataBlockHandle_in;
}


INode::INode()
{
  m_isDirectory = false;

  for (int i = 0; i < 10; i++)
    permissionData[i] = 0;
}

INode::INode(bool isDirectory_in, bool *permissionData_in)
{
  m_isDirectory = isDirectory_in;
  
  for (int i = 0; i < 10; i++)
    m_permissionData[i] = permissionData_in[i];
}


INode::~INode()
{
  if (m_rootDataHandle.m_nextDataHandle != nullptr)
    m_cleanINode(m_rootDataHandle.m_nextDataHandle);
}
