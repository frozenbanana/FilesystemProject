// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)
#ifndef INODE_H
#define INODE_H


#include <string>
#include <iostream>
<<<<<<< HEAD
#include <stdio.h>
=======
>>>>>>> 5c54fd232002c26a7ae69712ed6b916940d5ddd2

class DataBlockHandle
{
  private:
<<<<<<< HEAD
    int		*m_thisDataBlock;   // Data type STILL TO BE DETERMINED
=======
    //DATABLOCK_POINTER   *m_thisDataBlock;   // Data type STILL TO BE DETERMINED
    DataBlockHandle      *m_nextDataHandle;
>>>>>>> 5c54fd232002c26a7ae69712ed6b916940d5ddd2

  public:
    DataBlockHandle();
    ~DataBlockHandle();

<<<<<<< HEAD
	int*	getDataBlock();
	void	setDataBlock(int *dataBlock_in);

	DataBlockHandle      *m_nextDataHandle;
=======
    //*DataBlockHandle extendHandleList();
>>>>>>> 5c54fd232002c26a7ae69712ed6b916940d5ddd2
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
<<<<<<< HEAD

	DataBlockHandle* extendHandleList();
};

#endif
=======
};
>>>>>>> 5c54fd232002c26a7ae69712ed6b916940d5ddd2
