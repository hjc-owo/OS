#include "lib.h"

void umain() {
    volatile u_int *a = (volatile u_int *) 0x23333334;
    make_shared((void *) a);
    *a = 233;
    if (fork() == 0) {
        u_int ch = syscall_getenvid();
        *a = ch;
        while (*a == ch)
            syscall_yield();
        writef("parent is %x\n", *a);
    } else {
        while (*a == 233)
            syscall_yield();
        writef("child is %x\n", *a);
        *a = syscall_getenvid();
    }
}