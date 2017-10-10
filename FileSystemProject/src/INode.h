// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)
#ifndef INODE_H
#define INODE_H


#include <string>
#include <iostream>
#include <stdio.h>

class DataBlockHandle
{
  private:
    int		*m_thisDataBlock;   // Data type STILL TO BE DETERMINED

  public:
    DataBlockHandle();
    ~DataBlockHandle();

	int*	getDataBlock();
	void	setDataBlock(int *dataBlock_in);

	DataBlockHandle      *m_nextDataHandle;
};

class INode
{
  private:
    bool				m_isDirectory;
    DataBlockHandle		m_rootDataHandle;
    bool				m_permissionData[10];

	void				cleanAll();
    void				m_cleanNextDataHandle(DataBlockHandle *DataBlockHandle_in);

  public:
    INode();
    INode(bool isDirectory_in, bool *permissionData_in);
    ~INode();

	DataBlockHandle* extendHandleList();
};

#endif