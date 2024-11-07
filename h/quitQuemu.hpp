//
// Created by os on 6/21/24.
//

#ifndef PROJECT_BASE_V1_1_QUITQUEMU_HPP
#define PROJECT_BASE_V1_1_QUITQUEMU_HPP
#include "../lib/hw.h"
void quitQuemu(){
    //zavrsavanje programa
    uint32 memLoc = 0x100000;
    uint stopValue = 0x5555;
    __asm__ volatile("mv a1, %[broj] " : : [broj] "r" (memLoc));
    __asm__ volatile("mv a2, %[broj] " : : [broj] "r" (stopValue));
    __asm__ volatile("sw a2, 0(a1)");
}

#endif //PROJECT_BASE_V1_1_QUITQUEMU_HPP
