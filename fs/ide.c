/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurrs during the read of the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
/*** exercise 5.2 ***/
int ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs) {
    // 0x200: the size of a sector: 512 bytes.
    int offset_begin = secno * 0x200;
    int offset_end = offset_begin + nsecs * 0x200;
    int offset = 0;

    u_int zero = 0;
    u_int cur_offset = 0;

    while (offset_begin + offset < offset_end) {
        // Your code here
        // error occurred, then panic.
        cur_offset = offset_begin + offset;
        if (syscall_write_dev((u_int) & diskno, 0x13000010, 4) < 0)
            user_panic("ide_read panic");
        if (syscall_write_dev((u_int) & cur_offset, 0x13000000, 4) < 0)
            user_panic("ide_read panic");
        if (syscall_write_dev((u_int) & zero, 0x13000020, 4) < 0)
            user_panic("ide_read panic");
        u_int succ;
        if (syscall_read_dev((u_int) & succ, 0x13000030, 4) < 0)
            user_panic("ide_read panic");
        if (!succ)
            return 1;
        if (syscall_read_dev((u_int)(dst + offset), 0x13004000, 0x200) < 0)
            user_panic("ide_read panic");
        offset += 0x200;
    }
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurrs during the read of the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
/*** exercise 5.2 ***/
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs) {
    // Your code here
    int offset_begin = secno * 0x200;
    int offset_end = offset_begin + nsecs * 0x200;
    int offset = 0;

    u_int one = 1;
    u_int cur_offset = 0;

    // DO NOT DELETE WRITEF !!!
    writef("diskno: %d\n", diskno);

    while (offset_begin + offset < offset_end) {
        // copy data from source array to disk buffer.
        // if error occur, then panic.
        cur_offset = offset_begin + offset;
        if (syscall_write_dev((u_int)(src + offset), 0x13004000, 0x200) < 0)
            user_panic("ide_write panic");
        if (syscall_write_dev((u_int) & diskno, 0x13000010, 4) < 0)
            user_panic("ide_write panic");
        if (syscall_write_dev((u_int) & cur_offset, 0x13000000, 4) < 0)
            user_panic("ide_write panic");
        if (syscall_write_dev((u_int) & one, 0x13000020, 4) < 0)
            user_panic("ide_write panic");
        u_int succ;
        if (syscall_read_dev((u_int) & succ, 0x13000030, 4) < 0)
            user_panic("ide_write panic");
        offset += 0x200;
    }
}

int raid4_valid(u_int diskno) {
    return !ide_read(diskno, 0, (void *) 0x13004000, 1);
}

int raid4_write(u_int blockno, void *src) {
    int i;
    int invalid = 0;
    int check[0x50];
    user_bzero(check, 0x200);
    for (i = 0; i < 4; i++) {
        if (raid4_valid(i + 1)) {
            invalid++;
            ide_write(i + 1, 2 * blockno, src + i * 0x200, 1);
            int j;
            for (j = 0; j < 50; j++) {
                check[j] ^= *(int *) (src + i * 0x200 + j * 4);
            }
        }
    }
    ide_write(5, 2 * blockno, check, 2);
    return invalid;
}

int raid4_read(u_int blockno, void *dst) {
    int i;
    int invalid = 0;
    int check[0x50];
    user_bzero(check, 0x200);
    for (i = 0; i < 4; i++) {
        if (raid4_valid(i + 1)) {
            invalid++;
            ide_read(i + 1, 2 * blockno, dst + i * 0x200, 1);
            int j;
            for (j = 0; j < 50; j++) {
                check[j] ^= *(int *) (dst + i * 0x200 + j * 4);
            }
        }
    }
    return invalid;
}