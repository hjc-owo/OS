// user/sigtest.c
#include "lib.h"

int flag = 0;

void handle(int sig) {
    flag += 1;
    if (sig == 15)
        writef("%x: kill me baby!\n", syscall_getenvid());
    else if (sig == 18)
        writef("%x: child exited\n", syscall_getenvid());
}

void handle_segv(int sig) {
    writef("%x: segmentation fault\n", syscall_getenvid());
    exit();
}

void umain() {
    signal(15, handle);
    signal(18, handle);
    signal(11, handle_segv);

    int parent = syscall_getenvid();
    int ch = fork();
    if (ch == 0) {
        kill(parent, 15);
        ipc_recv(0, 0, 0);
        *(int *) NULL = 233;
    } else {
        while (!flag)
            syscall_yield();
        ipc_send(ch, 0, 0, 0);
        while (flag < 2)
            syscall_yield();
    }

    signal(15, 0);
    kill(0, 15);
    writef("this is unreachable");
}