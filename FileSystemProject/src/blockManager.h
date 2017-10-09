// Made by: Henry Bergstrom
// Manages datablock request Provides free datablocks
// Reclaims datablocks Avoid 
// Linear search with list

#pragma once
#include <stdio>
#include "block.h"

const static int MAX_BLOCKS = 200;
class BlockManager
{
    public:
        BlockManager() { this->freeBlocksList(MAX_BLOCKS);   };
        ~BlockManager() { this->freeBlocksList.erase(0, MAX_BLOCKS); };
        Block GetFreeBlock() { this->freeBlocksList.pop(); };
        bool ReclaimBlock(Block block){ this->freeBlocksList.push(block); };

    private:
        std::list<Block> freeBlocksList;

}



