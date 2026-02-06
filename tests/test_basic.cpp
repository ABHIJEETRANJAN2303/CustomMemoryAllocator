#include <iostream>
#include "MemoryAllocator.hpp"

int main()
{
    std::cout << "===== BASIC ALLOCATOR TEST =====\n";

    // Create allocator with 1 KB heap
    MemoryAllocator allocator(1024);

    allocator.printHeapLayout();
    allocator.printFreeList();

    // Allocate 100 bytes
    void *p1 = allocator.allocate(100);
    std::cout << "\nAllocated 100 bytes at " << p1 << "\n";

    allocator.printHeapLayout();
    allocator.printFreeList();

    // Allocate another 200 bytes
    void *p2 = allocator.allocate(200);
    std::cout << "\nAllocated 200 bytes at " << p2 << "\n";

    allocator.printHeapLayout();
    allocator.printFreeList();

    // Free the first pointer
    std::cout << "\nFree p1...\n";
    allocator.freeMemory(p1);

    allocator.printHeapLayout();
    allocator.printFreeList();

    // Free second pointer
    std::cout << "\nFree p2...\n";
    allocator.freeMemory(p2);

    allocator.printHeapLayout();
    allocator.printFreeList();

    std::cout << "===== BASIC TEST COMPLETE =====\n";
    return 0;
}
