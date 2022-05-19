// user/ipcrecv.c
#include "lib.h"

void umain() {
    u_int me = syscall_getenvid();
    u_int i, sum = 0, whos[3];
    for (i = 0; i < 10000; ++i)
        syscall_yield();
    for (i = 0; i < 3; ++i)
        sum += ipc_recv(&whos[i], 0, 0);

    int *buf = (int *) 0x60000000;
    syscall_mem_alloc(0, buf, PTE_V | PTE_R);
    buf[0] = sum;

    for (i = 0; i < 3; ++i)
        ipc_send(whos[i], i, buf, PTE_V | PTE_R);
    while (1);
}
