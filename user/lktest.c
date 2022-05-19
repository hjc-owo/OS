/* user/lktest.c */
#include "lib.h"

void umain() {
    u_int me = syscall_getenvid();
    while (syscall_try_acquire_console() != 0) {
        syscall_yield();
    }
    writef("I'm %x\n", me);
    syscall_release_console();

    while(1);
}