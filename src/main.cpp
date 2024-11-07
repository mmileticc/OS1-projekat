//
// Created by os on 6/22/24.
//
#include "../lib/hw.h"
#include "../test/printing.hpp"
#include "../h/quitQuemu.hpp"
#include "../h/riscv.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/tcb.hpp"
#include "../test/ConsumerProducer_CPP_Sync_API_test.hpp"
#include "../h/syscall_cpp.hpp"


void userMain();

void idleThreadBody(void *){
    while (true) {
        thread_dispatch();
    }
}

void wrapperUM(void*){
    userMain();
}
TCB *userMainTCB;
TCB *Main;
int main(){
    MemoryAllocator::initilaze();
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

    //main thread
    thread_create((thread_t *)(&Main), nullptr, nullptr);
    TCB::running = Main;
    //idle thread
    Thread idle(idleThreadBody, nullptr);
    idle.start();

    thread_create((thread_t *)(&userMainTCB), wrapperUM, nullptr);
    while(!userMainTCB->isFinished()){
        thread_dispatch();
    }
    //userMain();
    //producerConsumer_CPP_Sync_API();

    quitQuemu();
    return 0;
}