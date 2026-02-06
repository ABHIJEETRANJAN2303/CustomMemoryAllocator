#include "MemoryAllocator.hpp"
#include <cstdlib>
#include <iostream>

MemoryAllocator::MemoryAllocator(size_t heapSize)
    : heapStart(nullptr), totalHeapSize(heapSize), heapHead(nullptr)
{
    initializeHeap(heapSize);
}

MemoryAllocator::~MemoryAllocator()
{
    std::free(heapStart);
    heapStart = nullptr;
}

void MemoryAllocator::initializeHeap(size_t heapSize)
{
    heapStart = std::malloc(heapSize);
    if (!heapStart)
    {
        std::cerr << "Memory allocation failed.\n";
        std::abort();
    }

    BlockMetadata *first = reinterpret_cast<BlockMetadata *>(heapStart);
    first->size = heapSize - sizeof(BlockMetadata);
    first->isFree = true;
    first->next = nullptr;
    first->prev = nullptr;
    first->nextFree = nullptr;
    first->prevFree = nullptr;

    heapHead = first;
    freelist.insert(first);
}

void *MemoryAllocator::allocate(size_t size)
{
    if (size == 0)
        return nullptr;

    BlockMetadata *block = freelist.findFirstFit(size);
    if (!block)
        return nullptr;

    if (block->size > size + sizeof(BlockMetadata))
        splitBlock(block, size);

    freelist.remove(block);
    block->isFree = false;

    return reinterpret_cast<char *>(block) + sizeof(BlockMetadata);
}

BlockMetadata *MemoryAllocator::getBlockHeader(void *userPtr) const
{
    return reinterpret_cast<BlockMetadata *>(
        reinterpret_cast<char *>(userPtr) - sizeof(BlockMetadata));
}

void MemoryAllocator::freeMemory(void *ptr)
{
    if (!ptr)
        return;

    BlockMetadata *block = getBlockHeader(ptr);

    if (block->isFree)
    {
        std::cerr << "Double free detected!\n";
        return;
    }

    block->isFree = true;
    coalesce(block);
}

void MemoryAllocator::splitBlock(BlockMetadata *block, size_t requestedSize)
{
    size_t remaining = block->size - requestedSize - sizeof(BlockMetadata);
    if (remaining <= sizeof(BlockMetadata))
        return;

    char *addr = reinterpret_cast<char *>(block) + sizeof(BlockMetadata) + requestedSize;
    BlockMetadata *newBlock = reinterpret_cast<BlockMetadata *>(addr);

    newBlock->size = remaining;
    newBlock->isFree = true;
    newBlock->next = block->next;
    newBlock->prev = block;

    if (block->next)
        block->next->prev = newBlock;

    block->next = newBlock;
    block->size = requestedSize;

    freelist.insert(newBlock);
}

void MemoryAllocator::coalesce(BlockMetadata *block)
{
    auto safeRemove = [&](BlockMetadata *b)
    {
        if (!b)
            return;
        if (freelist.getHead() == b || b->prevFree || b->nextFree)
            freelist.remove(b);
    };

    BlockMetadata *left = block->prev;
    BlockMetadata *right = block->next;

    if (left && left->isFree)
    {
        safeRemove(left);
        safeRemove(block);

        left->size += sizeof(BlockMetadata) + block->size;
        left->next = block->next;

        if (block->next)
            block->next->prev = left;

        block = left;
    }

    if (right && right->isFree)
    {
        safeRemove(right);

        block->size += sizeof(BlockMetadata) + right->size;
        block->next = right->next;

        if (right->next)
            right->next->prev = block;
    }

    block->isFree = true;
    block->nextFree = nullptr;
    block->prevFree = nullptr;

    freelist.insert(block);
}

void MemoryAllocator::printHeapLayout() const
{
    std::cout << "----- Heap Layout -----\n";
    BlockMetadata *cur = heapHead;

    while (cur)
    {
        std::cout << "[Block @ " << cur << "] size=" << cur->size
                  << ", free=" << (cur->isFree ? "yes" : "no") << "\n";
        cur = cur->next;
    }

    std::cout << "------------------------\n";
}

void MemoryAllocator::printFreeList() const
{
    std::cout << "----- Free List -----\n";
    BlockMetadata *cur = freelist.getHead();

    while (cur)
    {
        std::cout << "[Free @ " << cur << "] size=" << cur->size << "\n";
        cur = cur->nextFree;
    }

    std::cout << "----------------------\n";
}
