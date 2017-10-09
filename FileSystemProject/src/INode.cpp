#include "INode.h"

INode::INode()
{
  m_isDirectory = false;
  m_name = "UNKNOWN";
  m_addressLocation = nullptr;

  for (int i = 0; i < 10; i++)
    permissionData[i] = 0;
}

INode::INode(bool isDirectory_in, std::string name_in, void *addressLocation_in, bool *permissionData)
{
  m_isDirectory = isDirectyory_in;
  m_name = name_in;
  m_addressLocation = addressLocation_in;
  
  for (int i = 0; i < 10; i++)
    m_permissionData[i] = permissionData[i];
}


INode::~INode()
{
  // NOTE: *m_addressLocation is never NEW'd and should therefore not be
  // deallocated here (more appropriate is within 'memblockdevice').
}
