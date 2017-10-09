// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)

#include <string>
#include <iostream>
#include <stdio>

class DataBlockHandle
{
  private:
    DATABLOCK_POINTER   *m_thisDataBlock;
    DataBloickHandle      *m_nextDataHandle;

  public:
    DataBlockHandle();
    ~DataBlockHandle();

    // Need to implement a function (m_extend()) to extend 'Triangle' list
}

class INode
{
  private:
    bool              m_isDirectoy;
    DataBlockHandle    m_rootDataHandle;
    bool              m_permissionData[10];

    void m_cleanINode(DataBlockHandle *DataBlockHandle_in);

  public:
    INode();
    INode(bool isDirectory_in, bool *permissionData_in);
    ~INode();
}
