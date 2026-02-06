#pragma once
#include <cstddef>
#include <cstdint>

// Force safe alignment for pointers & size_t
struct alignas(16) BlockMetadata
{
    size_t size;
    bool isFree;

    // Pad manually so struct layout is stable on ARM64
    uint8_t padding[7];

    BlockMetadata *next;
    BlockMetadata *prev;

    BlockMetadata *nextFree;
    BlockMetadata *prevFree;
};
