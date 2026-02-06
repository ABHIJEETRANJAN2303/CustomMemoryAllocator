#pragma once
#include "BlockMetadata.hpp"
#include "FreeList.hpp"
class MemoryAllocator
{
public:
    MemoryAllocator(size_t heapSize);
    ~MemoryAllocator();
    void *allocate(size_t size);
    void freeMemory(void *ptr);
    void printHeapLayout() const;
    void printFreeList() const;

private:
    void initializeHeap(size_t heapSize);
    void splitBlock(BlockMetadata *block, size_t requestedSize);
    void coalesce(BlockMetadata *block);
    BlockMetadata *getBlockHeader(void *userPtr) const;

private:
    void *heapStart;
    size_t totalHeapSize;
    FreeList freelist;
    BlockMetadata *heapHead;
};