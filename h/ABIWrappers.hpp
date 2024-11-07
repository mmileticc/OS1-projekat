//
// Created by os on 6/24/24.
//

#ifndef PROJECT_BASE_V1_1_ABIWRAPPERS_HPP
#define PROJECT_BASE_V1_1_ABIWRAPPERS_HPP
#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"
namespace ABI {
    void memAllocWrapper(uint64 a1);

    void memFreeWrapper(uint64 a1);

    void threadCreateWrapper(uint64 handle, uint64 body, uint64 arg, uint64 stackSpace);

    void threadExitWrapper();

    void threadDispatchWrapper();

    void semOpenWrapper(uint64 handle, uint64 init);

    void semCloseWrapper(uint64 handle);

    void semWaitWrapper(uint64 handleId);

    void semSignalWrapper(uint64 handleId);

    void semTryWaitWrapper(uint64 handleId);

    void getcWrapper();

    void putcWrapper(uint64 c);
}
#endif //PROJECT_BASE_V1_1_ABIWRAPPERS_HPP
