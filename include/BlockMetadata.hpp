#pragma once
#include <cstddef>
#include <cstdint>

struct alignas(16) BlockMetadata
{
    size_t size;
    bool isFree;

    uint8_t padding[7];

    BlockMetadata *next;
    BlockMetadata *prev;

    BlockMetadata *nextFree;
    BlockMetadata *prevFree;
};
