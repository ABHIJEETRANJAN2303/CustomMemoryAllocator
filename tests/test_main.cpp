#include "../include/MemoryAllocator.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

static const size_t HEAP_SIZE = 20480; // ~20 KB
static const int OPERATIONS = 2000;    // number of random operations

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "===== RANDOM STRESS TEST =====\n";

    MemoryAllocator allocator(HEAP_SIZE);

    std::vector<void *> ptrs;
    ptrs.reserve(1000);

    for (int iter = 0; iter < 5; iter++)
    {
        std::cout << "\n--- ITERATION " << iter << " ---\n";

        // Perform random allocate/free operations
        for (int i = 0; i < OPERATIONS; i++)
        {
            int action = std::rand() % 2;

            if (action == 0 || ptrs.empty())
            {
                // Allocate random size between 1 and 256 bytes
                size_t size = (std::rand() % 256) + 1;
                void *p = allocator.allocate(size);
                if (p)
                    ptrs.push_back(p);
            }
            else
            {
                // Free a random pointer
                int idx = std::rand() % ptrs.size();
                allocator.freeMemory(ptrs[idx]);
                ptrs.erase(ptrs.begin() + idx);
            }
        }

        // Free all remaining allocations
        for (void *p : ptrs)
            allocator.freeMemory(p);

        ptrs.clear();

        // Show the heap to verify full recovery
        allocator.printHeapLayout();
        allocator.printFreeList();
    }

    std::cout << "\n===== STRESS TEST COMPLETED =====\n";
    return 0;
}
