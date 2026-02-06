#include "FreeList.hpp"

FreeList::FreeList() : head(nullptr) {}

void FreeList::insert(BlockMetadata *block)
{
    block->prevFree = nullptr;
    block->nextFree = head;

    if (head)
        head->prevFree = block;

    head = block;
}

void FreeList::remove(BlockMetadata *block)
{
    if (block->prevFree)
        block->prevFree->nextFree = block->nextFree;
    else
        head = block->nextFree;

    if (block->nextFree)
        block->nextFree->prevFree = block->prevFree;

    block->prevFree = nullptr;
    block->nextFree = nullptr;
}

BlockMetadata *FreeList::findFirstFit(size_t size)
{
    BlockMetadata *cur = head;
    while (cur)
    {
        if (cur->size >= size)
            return cur;
        cur = cur->nextFree;
    }
    return nullptr;
}
