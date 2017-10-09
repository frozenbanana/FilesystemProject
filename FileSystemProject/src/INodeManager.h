#include <string>
#include <iostream>
#include <stdio>
#include "INode.h"

#define INODE_COUNT 250





class INode_Handle  // Acts as a shell & thereby a 'slot' for a single free INode (INode included)
{
  private:
    INode_Handle           *m_underneath;
    INode                  m_me

  public:
    INode_Handle();
    ~INode_Handle(); 
}





class INodeManager
{
    private:
      int                 m_FreeINodeCount;
      INode_Handle        *m_stackTop
      
    public:  
      INodeManager();
      ~INodeManager();
}
