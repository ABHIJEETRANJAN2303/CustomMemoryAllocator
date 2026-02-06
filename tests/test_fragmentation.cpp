#include <iostream>
#include <vector>
#include "MemoryAllocator.hpp"

int main()
{
    std::cout << "===== FRAGMENTATION TEST =====\n";

    // Create allocator with 2 KB heap
    MemoryAllocator allocator(2048);

    allocator.printHeapLayout();
    allocator.printFreeList();

    std::vector<void *> ptrs;

    std::cout << "\nAllocating 10 blocks of 100 bytes...\n";

    for (int i = 0; i < 10; i++)
    {
        void *p = allocator.allocate(100);
        std::cout << "Allocated block " << i << " at " << p << "\n";
        ptrs.push_back(p);
    }

    allocator.printHeapLayout();
    allocator.printFreeList();

    std::cout << "\nFreeing even index blocks...\n";

    for (int i = 0; i < 10; i += 2)
    {
        std::cout << "Freeing p[" << i << "]\n";
        allocator.freeMemory(ptrs[i]);
    }

    allocator.printHeapLayout();
    allocator.printFreeList();

    std::cout << "\nFreeing odd index blocks...\n";

    for (int i = 1; i < 10; i += 2)
    {
        std::cout << "Freeing p[" << i << "]\n";
        allocator.freeMemory(ptrs[i]);
    }

    allocator.printHeapLayout();
    allocator.printFreeList();

    std::cout << "\n===== FRAGMENTATION TEST COMPLETE =====\n";
    return 0;
}
