// Here we implement INode class
// See link: https://en.wikipedia.org/wiki/Inode_pointer_structure
// Store attributes and disk blocks location(s)
#ifndef INODE_H
#define INODE_H


#include <string>
#include <iostream>
#include <stdio.h>
#include "block.h"

class BlockHandle
{
  private:
    Block		*m_thisBlock;

  public:
    BlockHandle();
    ~BlockHandle();

  	Block*	GetBlock();
  	void	  SetBlock(int *Block_in);

	  BlockHandle      *m_nextHandle; // Public in-case someone else needs to 'step'
};

class INode
{
  private:
    bool	      			m_isDirectory;
    bool			      	m_permissionData[10];

	  void				CleanAll();
    void				CleanNextHandle(BlockHandle *BlockHandle_in);

    void        ExtendList(BlockHandle* rootHandle_in, int blockCount_in);
    void        InsertList(BlockHandle* rootHandle_in, Block* *BlockArray_in, int BlockCount_in);

  public:
    INode();
    INode(bool isDirectory_in, bool *permissionData_in);
    ~INode();

    BlockHandle   		m_rootHandle;     // rootHandle public to gain access

	/*- - - - - FUNCTION COMMENTS - - - - -   // NEED TO UPDATE THIS DESCRIPTION
   * LAST
	 • Extends the linked list within the INode
	 • RECAP: Members of linked list point to 1 Block each
	 • RETURN VALUE: Address of new 'BlockHandle' member*/
	  bool  InsertBlocks(int BlockCount_in, Block* *BlockArray_in);
};

#endif
