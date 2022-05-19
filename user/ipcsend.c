#include "lib.h"

void umain() {
    u_int me = syscall_getenvid();
    u_int dst = envs[3].env_id;
    u_int val = ENVX(me);
    ipc_send(dst, val, 0, 0);

    u_int who;
    int *buf = (int *) 0x60000000;
    ipc_recv(&who, buf, 0);
    writef("%x: got %d from %x\n", me, buf[0], who);

    while (1);
}