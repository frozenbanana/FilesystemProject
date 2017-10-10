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

int* DataBlockHandle::GetDataBlock()
{
	return m_thisDataBlock;
}

void DataBlockHandle::SetDataBlock(int *dataBlock_in)
{
	m_thisDataBlock = dataBlock_in;
}



///////////////////////////////////////////////////////////////////////////////////////////////




// PRIVATE FUNCTIONS

/*- - - - - FUNCTION COMMENTS - - - - -
Makes use of two clean functions
 • CleanAll() gives initial access to root
 • CleanNextDataHandle recursively deletes all past root*/
void INode::CleanAll()
{
	if (m_rootDataHandle.m_nextDataHandle != nullptr)
		m_CleanNextDataHandle(m_rootDataHandle.m_nextDataHandle);

	// No 'delete' due to static root
}

/*- - - - FUNCTION COMMENTS - - - - -
See 'Function Comments' for 'CleanAll() function*/
void INode::m_CleanNextDataHandle(DataBlockHandle *DataBlockHandle_in)
{
  if (DataBlockHandle_in->m_nextDataHandle != nullptr)
	  m_CleanNextDataHandle(DataBlockHandle_in->m_nextDataHandle);

  delete DataBlockHandle_in;	// Recursively calling this function down until,
}								// but not including, the root.




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


DataBlockHandle* INode::ExtendHandleList()
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