#ifndef _syscall_c
#define _syscall_c
#include "../lib/hw.h"

/*Nit se kreira sa podrazumevanom veličinom steka ( DEFAULT_STACK_SIZE ) i
podrazumevanom veličinom vremenskog odreska ( DEFAULT_TIME_SLICE ). Ove konstante
deklarisane su u hw.h , a definisane u hw.lib :
extern const size_t DEFAULT_STACK_SIZE;
extern const time_t DEFAULT_TIME_SLICE;
Memorijski prostor koji je slobodan za alokaciju počinje od adrese HEAP_START_ADDR ,
a završava se na adresi HEAP_END_ADDR-1 . Ove konstante, kao i konstanta MEM_BLOCK_SIZE ,
deklarisane su u hw.h , a definisane u hw.lib :
extern const void* HEAP_START_ADDR, HEAP_END_ADDR;
extern const size_t MEM_BLOCK_SIZE;*/



void* mem_alloc (size_t size);  //0x01

int mem_free (void*);  //0x02

class _thread;
typedef _thread* thread_t;
int thread_create ( thread_t* handle, void(*body)(void*), void* arg);  //0x11

int thread_exit ();  //0x12

void thread_dispatch ();  //0x13

class _sem;
typedef _sem* sem_t;
int sem_open (sem_t* handle, unsigned init);  //0x21

int sem_close (sem_t handle);  //0x22

int sem_wait (sem_t id);  //0x23

int sem_signal (sem_t id);  //0x24

int sem_timedwait(sem_t id,time_t timeout); //0x25

int sem_trywait(sem_t id); //0x26

typedef unsigned long time_t;
int time_sleep (time_t);  //0x31

const int EOF = -1;
char getc ();  //0x41

void putc (char);  //0x42

#endif //_syscall_c