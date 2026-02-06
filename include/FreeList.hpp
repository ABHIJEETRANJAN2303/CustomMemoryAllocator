#pragma once
#include "BlockMetadata.hpp"
class FreeList
{
public:
    FreeList();
    void insert(BlockMetadata *block);
    void remove(BlockMetadata *block);
    BlockMetadata *findFirstFit(size_t size);
    BlockMetadata *getHead() const
    {
        return head;
    }

private:
    BlockMetadata *head;
};