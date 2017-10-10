#include "INode.h"

// PUBLIC FUNCTIONS

DataBlockHandle::DataBlockHandle()
{
  m_thisDataBlock = nullptr;
  m_nextDataHandle = nullptr;
}

DataBlockHandle::~DataBlockHandle()
{

}

int* DataBlockHandle::getDataBlock()
{
	return m_thisDataBlock;
}

void DataBlockHandle::setDataBlock(int *dataBlock_in)
{
	m_thisDataBlock = dataBlock_in;
}



///////////////////////////////////////////////////////////////////////////////////////////////




// PRIVATE FUNCTIONS

void INode::cleanAll()
{
	if (m_rootDataHandle.m_nextDataHandle != nullptr)
		m_cleanNextDataHandle(m_rootDataHandle.m_nextDataHandle);
}

void INode::m_cleanNextDataHandle(DataBlockHandle *DataBlockHandle_in)
{
  if (DataBlockHandle_in->m_nextDataHandle != nullptr)
	  m_cleanNextDataHandle(DataBlockHandle_in->m_nextDataHandle);

  delete DataBlockHandle_in;
  delete this;
}



// PUBLIC FUNCTIONS

INode::INode()
{
  m_isDirectory = false;

  for (int i = 0; i < 10; i++)
    m_permissionData[i] = 0;
}

INode::INode(bool isDirectory_in, bool *permissionData_in)
{
  m_isDirectory = isDirectory_in;
  
  for (int i = 0; i < 10; i++)
    m_permissionData[i] = permissionData_in[i];
}



INode::~INode()
{

}


DataBlockHandle* INode::extendHandleList()
{
	DataBlockHandle *tempHandle;

	if (m_rootDataHandle.m_nextDataHandle != nullptr)
	{
		tempHandle = m_rootDataHandle.m_nextDataHandle;

		while (tempHandle->m_nextDataHandle != nullptr)
			tempHandle = tempHandle->m_nextDataHandle;

		tempHandle->m_nextDataHandle = new DataBlockHandle;
	}

	return tempHandle->m_nextDataHandle;
}