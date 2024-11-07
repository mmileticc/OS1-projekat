//
// Created by os on 6/24/24.
//
#include "../h/ABIWrappers.hpp"
#include "../h/tcb.hpp"
#include "../h/Sem.hpp"
#include "../lib/console.h"
#include "../lib/mem.h"

void ABI::memAllocWrapper(uint64 a1) {
    uint64 size = a1;
    MemoryAllocator::mem_alloc(size);
    //__mem_alloc(size);
}

void ABI::memFreeWrapper(uint64 a1) {
    MemoryAllocator::mem_free((void *) a1);
    //__mem_free((void*)a1);
}
//int thread_create ( thread_t* handle, void(*start_routine)(void*), void* arg, void* stackSpace);
void ABI::threadCreateWrapper(uint64 handle, uint64 body, uint64 arg, uint64 stackSpace) {
    TCB** myHandle = (TCB**) handle;
    TCB::threadCreate(myHandle,
                      reinterpret_cast<void (*)(void *)>(body),
                       reinterpret_cast<void *>(arg),
                       reinterpret_cast<void *>(stackSpace));

}

void ABI::threadExitWrapper() {
    TCB::thread_exit();
}

void ABI::threadDispatchWrapper() {
    //bespotrebno al je ljepo
}

void ABI::semOpenWrapper(uint64 handle, uint64 init){
    Sem** sem = (Sem**) handle;
    *sem = Sem::createSem(init);
}

void ABI::semCloseWrapper(uint64 handle){
    Sem* sem = (Sem*)handle;
    Sem::closeSem(sem);
}

void ABI::semWaitWrapper(uint64 handleId){
    Sem* sem = (Sem*) handleId;
    sem->wait();
}

void ABI::semSignalWrapper(uint64 handleId){
    Sem* sem = (Sem*) handleId;
    sem->signal();

}

void ABI::semTryWaitWrapper(uint64 handleId){
    Sem* sem = (Sem*) handleId;
    sem->tryWait();
}

void ABI::getcWrapper(){
    __getc();
}

void ABI::putcWrapper(uint64 c){
    char cc = (char) c;
    __putc(cc);

}

