//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_TCB_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_TCB_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"
#include "syscall_c.hpp"
#include "../test/printing.hpp"

enum threadNames
{
    mainThread = 1,
    consoleThread = 4,
    idleThread = 2,
    userMainThread = 3
};
// Thread Control Block
class TCB
{
public:
    ~TCB() { delete[] stack; }

    bool isFinished() const { return finished; }
    void setFinished(bool value) { finished = value; }

    bool isBlocked() const { return blocked; }
    void setBlocked(bool value) { blocked = value; }

    bool isSys() const {return sys;}

    uint64 getTimeSlice() const { return timeSlice; }

    using Body = void (*)(void *);

    static TCB *createThread(Body body, void* arg, void* stackSpace);

    //int thread_create ( thread_t* handle, void(*body)(void*), void* arg, void* stackSpace);  //0x11
    static int threadCreate (TCB** handle, void(*body)(void*), void* arg, void* stackSpace);

    static int thread_exit();

    static void yield();

    static TCB *running;
    void* operator new(size_t size);
    void* operator new[](size_t size);
    void operator delete(void* ptr);
    void operator delete[](void* ptr);

    static void dispatch();
private:
    TCB(Body body, void* arg, void* stackSpace, uint64 timeSlice) :
            body(body),
            arg(arg),
            stack(body != nullptr ? (uint64*) stackSpace : nullptr),
            context({(uint64) &threadWrapper,
                     stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE/8] : 0
                    }),
            timeSlice(timeSlice),
            finished(false),
            blocked(false),
            sys(true),
            nextSem(nullptr)
    {
        id = cnt++;

        if (id != mainThread && id != idleThread ) sys = false;
        if (body != nullptr) { Scheduler::put(this); }

    }

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    void* arg;
    uint64 *stack;
    Context context;
    uint64 timeSlice;
    bool finished;
    bool blocked;
    bool sys;
    TCB *nextSem;


    static int cnt;

    friend class Riscv;
    friend class Sem;

    static void threadWrapper();

    static void contextSwitch(Context *oldContext, Context *runningContext);

    int id;


    static uint64 timeSliceCounter;

    //static uint64 constexpr STACK_SIZE = 1024;
    static uint64 constexpr TIME_SLICE = 2;
};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_TCB_HPP
