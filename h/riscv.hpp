//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_RISCV_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_RISCV_HPP

#include "../lib/hw.h"

class Riscv
{
public:

    static void popA0();

    // pop sstatus.spp and sstatus.spie bits (has to be a non inline function)
    static void popSppSpie();

    // read register scause
    static uint64 r_scause();

    // write register scause
    static void w_scause(uint64 scause);

    // read register sepc
    static uint64 r_sepc();

    // write register sepc
    static void w_sepc(uint64 sepc);

    // read register stvec
    static uint64 r_stvec();

    // write register stvec
    static void w_stvec(uint64 stvec);

    // read register stval
    static uint64 r_stval();

    // write register stval
    static void w_stval(uint64 stval);

    enum BitMaskSip
    {
        SIP_SSIP = (1 << 1),
        SIP_STIP = (1 << 5),
        SIP_SEIP = (1 << 9),
    };

    // mask set register sip
    static void ms_sip(uint64 mask);

    // mask clear register sip
    static void mc_sip(uint64 mask);

    // read register sip
    static uint64 r_sip();

    // write register sip
    static void w_sip(uint64 sip);

    enum BitMaskSstatus
    {
        SSTATUS_SIE = (1 << 1),
        SSTATUS_SPIE = (1 << 5),
        SSTATUS_SPP = (1 << 8),
    };

    // mask set register sstatus
    static void ms_sstatus(uint64 mask);

    // mask clear register sstatus
    static void mc_sstatus(uint64 mask);

    // read register sstatus
    static uint64 r_sstatus();

    // write register sstatus
    static void w_sstatus(uint64 sstatus);

    // supervisor trap
    static void supervisorTrap();

    static void pushRegisters();

    static void popRegisters();


// read register ao
    static uint64 r_a0();
// read register a1
    static uint64 r_a1();
// read register a2
    static uint64 r_a2();
// read register a3
    static uint64 r_a3();
// read register a4
    static uint64 r_a4();


    //system id codes enum
    enum sysId{
        memAlloc = 0x01,
        memFree = 0x02,
        threadCreate = 0x11,
        threadExit = 0x12,
        threadDispatch = 0x13,
        semOpen = 0x21,
        semClose = 0x22,
        semWait = 0x23,
        semSignal = 0x24,
        semTrywait = 0x26,
        //------------------ za 20p

        semTimedwait = 0x25,
        timeSleat = 0x31,
        getC = 0x41,
        putC = 0x42
    };
    static void sysCallWraper(...);

private:

    // supervisor trap handler
    static void handleSupervisorTrap();



};

inline uint64 Riscv::r_scause()
{
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r"(scause));
    return scause;
}

inline void Riscv::w_scause(uint64 scause)
{
    __asm__ volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
}

inline uint64 Riscv::r_sepc()
{
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}

inline void Riscv::w_sepc(uint64 sepc)
{
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
}

inline uint64 Riscv::r_stvec()
{
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}

inline void Riscv::w_stvec(uint64 stvec)
{
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}

inline uint64 Riscv::r_stval()
{
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}

inline void Riscv::w_stval(uint64 stval)
{
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}

inline void Riscv::ms_sip(uint64 mask)
{
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sip(uint64 mask)
{
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sip()
{
    uint64 volatile sip;
    __asm__ volatile ("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}

inline void Riscv::w_sip(uint64 sip)
{
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}

inline void Riscv::ms_sstatus(uint64 mask)
{
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sstatus(uint64 mask)
{
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sstatus()
{
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}

inline void Riscv::w_sstatus(uint64 sstatus)
{
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}
// read register a0
inline uint64 Riscv::r_a0() {
    uint64 volatile a0;
    __asm__ volatile("mv %0, a0" : "=r" (a0));
    return a0;
}
// read register a1
inline uint64 Riscv::r_a1() {
    uint64 volatile a1;
    __asm__ volatile("ld %0, 88(s0)" : "=r" (a1));
    return a1;
    /*uint64 volatile a0;
    __asm__ volatile("mv %0, a1" : "=r" (a0));
    return a0;*/
}
// read register a2
inline uint64 Riscv::r_a2() {
    uint64 volatile a2;
    __asm__ volatile("ld %0, 96(s0)" : "=r" (a2));
    return a2;
    /*uint64 volatile a0;
    __asm__ volatile("mv %0, a2" : "=r" (a0));
    return a0;*/
}
// read register a3
inline uint64 Riscv::r_a3() {
    uint64 volatile a3;
    __asm__ volatile("ld %0, 104(s0)" : "=r" (a3));
    return a3;
    /*uint64 volatile a0;
    __asm__ volatile("mv %0, a3" : "=r" (a0));
    return a0;*/
}
// read register a4
inline uint64 Riscv::r_a4() {
    uint64 volatile a4;
    __asm__ volatile("ld %0, 112(s0)" : "=r" (a4));
    return a4;
    /*uint64 volatile a0;
    __asm__ volatile("mv %0, a4" : "=r" (a0));
    return a0;*/
}



#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_RISCV_HPP
