//
// Created by os on 6/22/24.
//

#ifndef PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#include "../lib/hw.h"

struct memSegment{
    size_t numOfBlock;
    size_t startingAddr;
    memSegment* next;

};

class MemoryAllocator{
public:

    static void* mem_alloc (size_t numOfBlocks);

    static int mem_free (void*);

    static void initilaze();

    struct memSeg {
        size_t numOfBlocks;
        memSeg* next;
        memSeg* prev = nullptr;
    };
    static memSeg* freeSegHead;
    static size_t memSegSize;

private:
    MemoryAllocator(){};

    static void tryToMerge(memSeg *main, memSeg *curr);



};

#endif //PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
