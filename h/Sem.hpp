//
// Created by os on 6/26/24.
//

#ifndef PROJECT_BASE_V1_1_SEM_HPP
#define PROJECT_BASE_V1_1_SEM_HPP

#include "tcb.hpp"
#include "../h/list.hpp"

class Sem {
public:
    Sem (unsigned init) : dealoc(false), val(init), head(nullptr), tail(nullptr){}

    int wait ();
    void signal ();
    int tryWait();

    int getValue () const { return val; }

    bool isDealocated() const {return dealoc;}
    void setDealoc(bool value) { dealoc = value;}

    static Sem* createSem(uint64 init);

    static int closeSem(Sem*);
    void* operator new(size_t size);
    void* operator new[](size_t size);
    void operator delete(void* ptr);
    void operator delete[](void* ptr);
private:
    bool dealoc;
    int val;
    TCB* head;
    TCB* tail;

    void block();
    void unblock();

};

#endif //PROJECT_BASE_V1_1_SEM_HPP

