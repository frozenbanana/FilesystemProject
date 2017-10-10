// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)

#include <string>
#include <iostream>

class DataBlockHandle
{
  private:
    //DATABLOCK_POINTER   *m_thisDataBlock;   // Data type STILL TO BE DETERMINED
    DataBlockHandle      *m_nextDataHandle;

  public:
    DataBlockHandle();
    ~DataBlockHandle();

    //*DataBlockHandle extendHandleList();
};

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
};
