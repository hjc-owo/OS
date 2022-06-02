#include "fs.h"
#include "lib.h"
#include <mmu.h>

/* 一个block的数据 */
int data[8][128];
/* 一个block对应的2个校验码扇区 */
int check[2][128] = {
        {12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 60, 0, 60, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,   0, 4,   0, 124, 0, 124, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 60, 0, 60, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,   0, 4,   0, 252, 0, 252, 0, 4,  0, 4,  0, 12, 0},
        {4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 60, 0, 60, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 124, 0, 124, 0, 4,   0, 4,   0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 60, 0, 60, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 28, 0, 28, 0, 4,  0, 4,  0, 12, 0, 12, 0, 4,  0, 4,  0, 252, 0, 252, 0, 4,   0, 4,   0, 12, 0, 12, 0, 4,  0}
};
int read_data[8][128];

/* 创建一个磁盘块的数据 */
void init_data() {
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 128; j++) {
            data[i][j] = i + j + 7;
        }
    }
}

/* 打印数据 */
void print_data(int data[], const char *prefix, int size) {
    writef("%s", prefix);
    int i;
    for (i = 0; i < size; i++) {
        if (i != 0 && i % 128 == 0) writef("\n");
        writef("%d ", data[i]);
    }
    writef("\n");
}

void check_raid4_write(int blockno) {
    if (!raid4_valid(blockno)) return;
    int read[256], *std1, *std2, j;
    ide_read(blockno, 22, read, 1);
    ide_read(blockno, 23, read + 128, 1);
    std1 = blockno == 5 ? check[0] : data[blockno - 1];
    std2 = blockno == 5 ? check[1] : data[blockno + 3];
    for (j = 0; j < 128; j++) {
        if (read[j] != std1[j]) {
            writef("Data written in disk %d is wrong\n", blockno);
            print_data(std1, "Expected data: \n", 128);
            print_data(read, "Get data: \n", 128);
            user_panic("");
        }
        if (read[j + 128] != std2[j]) {
            writef("Data written in disk %d is wrong\n", blockno);
            print_data(std2, "Expected data: \n", 128);
            print_data(read + 128, "Get data: \n", 128);
            user_panic("");
        }
    }
}

void check_raid4_read(int blockno) {
    if (!raid4_valid(blockno)) return;
    int j;
    for (j = 0; j < 128; j++) {
        if (read_data[blockno - 1][j] != data[blockno - 1][j]) {
            writef("Data read from disk %d is wrong\n", blockno);
            print_data(data[blockno - 1], "Expected data: \n", 128);
            print_data(read_data[blockno - 1], "Get data: \n", 128);
            user_panic("");
        }
        if (read_data[blockno + 3][j] != data[blockno + 3][j]) {
            writef("Data read from disk %d is wrong\n", blockno);
            print_data(data[blockno + 3], "Expected data: \n", 128);
            print_data(read_data[blockno + 3], "Get data: \n", 128);
            user_panic("");
        }
    }
}

void umain() {
    int i, j, r;
    /* 获取磁盘状态 */
    writef("disk valid are: ");
    for (i = 1; i <= 5; i++) {
        writef("%d, ", raid4_valid(i));
    }
    writef("\n");

    init_data();
    print_data(data[0], "Standard data is: \n", 1024);
    print_data(check[0], "Standard checksum is: \n", 256);
    /* 检查raid4_write */
    r = raid4_write(11, data[0]);
    writef("raid4_write: %d disk(s) are damaged\n", r);
    for (i = 1; i <= 5; i++) {
        check_raid4_write(i);
    }
    /* 检查raid4_read */
    r = raid4_read(11, read_data[0]);
    writef("raid4_read: %d disk(s) are damaged\n", r);
    if (r <= 1) {
        for (i = 1; i <= 4; i++) {
            check_raid4_read(i);
        }
    }
    /* 检查无磁盘损坏时的校验和返回值 */
    if (r == 0) {
        ide_write(1, 22, check[1], 1);
        r = raid4_read(11, read_data[0]);
        if (r != -1) {
            writef("raid4_read expect to return -1\n");
            user_panic("");
        }
    }
    writef("Your raid4 write & read are basically correct\n");
}