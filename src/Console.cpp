//
// Created by os on 6/26/24.
//


#include "../h/syscall_cpp.hpp"

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}
