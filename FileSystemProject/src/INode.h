// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)

#include <string>
#include <iostream>
#include <stdio>

class INode
{
  private:
    bool          m_isDirectoy;
    std::string   m_name;
    void          *m_addressLocation;
    bool          m_permissionData[10]; 

  public:
    INode();
    ~INode();
}
