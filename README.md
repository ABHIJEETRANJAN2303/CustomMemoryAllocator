# Custom Memory Allocator (C++17)



A lightweight, custom memory allocator implemented from scratch in C++17. This project simulates a heap environment to perform manual memory management without relying on the standard `malloc`/`free` for individual allocations.

It features **block splitting**, **coalescing**, and an **explicit free-list** strategy, serving as a comprehensive systems-level learning resource.

---

## 🚀 Features

- **Fixed-Size Heap:** Manages a pre-allocated contiguous chunk of memory.
- **Explicit Free List:** Uses a **First-Fit** strategy for $O(n)$ allocation speed.
- **Block Metadata:** Embedded header information in every block (doubly linked list for physical traversal).
- **Efficient Memory Use:** - **Splitting:** Large free blocks are split to minimize internal fragmentation.
  - **Coalescing:** Adjacent free blocks are automatically merged on deallocation to prevent external fragmentation.
- **Robust Testing:** Includes unit tests for fragmentation handling and stress testing.

---

## 🛠 Implementation Details

### 1. Block Layout (Metadata)
Every memory block consists of a header (metadata) followed immediately by the payload (user data). The metadata is embedded directly into the heap.



```text
+------------------------+  <-- Block Start Address
|   BlockMetadata        |
|  [ size, isFree ]      |
|  [ prev, next   ]      |  <-- Physical Neighbors (for Coalescing)
|  [ prevFree, nextFree ]|  <-- Logical Neighbors (for Free List)
+------------------------+
|                        |
|    User Allocation     |  <-- Returned Pointer
|       (Payload)        |
|                        |
+------------------------+
Physical Linking: prev and next pointers allow traversal of the heap effectively to merge adjacent blocks during free().

Logical Linking: prevFree and nextFree pointers allow the allocator to skip over occupied blocks and only scan free blocks during alloc().

2. Free List Strategy (First-Fit)
The allocator maintains a singly linked list pointing only to free blocks. When an allocation is requested, it iterates through this list and selects the first block capable of holding the requested size.

3. Splitting & Coalescing
Splitting: If a chosen block is significantly larger than the requested size, it is split into two: one occupied block and one smaller free block.

Coalescing: When a block is freed, the allocator checks its physical neighbors (prev and next). If they are also free, they are merged into one large block to reduce fragmentation.

💻 Usage
To use the allocator in your project, include the header and instantiate the MemoryAllocator with your desired heap size.

C++
#include "MemoryAllocator.hpp"
#include <iostream>

int main() {
    // 1. Initialize allocator with 1024 bytes of heap memory
    MemoryAllocator allocator(1024);
    allocator.init();

    // 2. Allocate memory (returns void*)
    void* ptr1 = allocator.alloc(256);
    
    // 3. Cast and use memory
    int* data = static_cast<int*>(ptr1);
    *data = 42;

    // 4. Free memory (automatically coalesces if possible)
    allocator.free(ptr1);

    return 0;
}
📂 Project Structure
Plaintext
.
├── CMakeLists.txt       # Build configuration
├── src/
│   ├── MemoryAllocator.cpp
│   └── FreeList.cpp
├── include/
│   ├── MemoryAllocator.hpp
│   ├── FreeList.hpp
│   └── BlockMetadata.hpp
└── tests/
    ├── test_basic.cpp          # Simple alloc/free checks
    ├── test_fragmentation.cpp  # Tests splitting and merging logic
    └── test_main.cpp           # Entry point for testing framework
⚙️ Build & Run
Ensure you have a C++17 compliant compiler (GCC/Clang/MSVC) and CMake installed.

1. Build the project
Bash
mkdir build
cd build
cmake ..
make
2. Run the tests
Bash
# Run basic functionality tests
./test_basic

# Run fragmentation and coalescing tests
./test_fragmentation

# Run the main test suite
./test_main
🧠 Learning Outcomes
This project demonstrates core systems programming concepts:

Pointer Arithmetic: Traversing raw memory addresses and managing offsets.

Manual Heap Simulation: Understanding how the OS hands memory to processes.

Data Alignment & Padding: Handling memory alignment requirements.

Memory Fragmentation: Visualizing external vs. internal fragmentation.

Safe Resource Management: Implementing robust splitting and merging logic to prevent leaks and corruption.