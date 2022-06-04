#include "lib.h"

void umain() {
    int fdnum = open("/newmotd", O_RDWR);
    if (fdnum < 0) {
        user_panic("open failed");
    }
    seek(fdnum, 2);
    int pid = fork();
    if (pid == 0) {
        struct Fd *fd;
        if (fd_lookup(fdnum, &fd) < 0) {
            writef("[N]\n");
        } else {
            writef("[Y] THE CHILD: fd->fd_offset = %d\n", fd->fd_offset);
        }
    }
}