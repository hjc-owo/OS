#include "fs.h"
#include "lib.h"
#include <mmu.h>

/* 创建数据 */
void init_data(int data[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        data[i] = i + size;
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

void umain(void) {
    /* 检查 time read */
    int time = time_read();
    writef("current time is: %d\n", time);
    /* 检查 raid0 write & read */
    int data[2][128], read[2][128], i;
    init_data(data[0], 256);
    print_data(data[0], "Standard data is: \n", 256);
    raid0_write(25, data[0], 2);    /* 写入扇区 25 26*/
    ide_read(2, 12, read[0], 1);
    ide_read(1, 13, read[1], 1);
    for (i = 0; i < 128; i++) {
        if (data[0][i] != read[0][i] || data[1][i] != read[1][i]) {
            print_data(read[0], "Data you wrote in disk is: \n", 256);
            user_panic("Data written by raid0_write is incorrect");
        }
    }
    user_bzero(read[0], 1024);
    raid0_read(25, read[0], 2);
    for (i = 0; i < 128; i++) {
        if (data[0][i] != read[0][i] || data[1][i] != read[1][i]) {
            print_data(read[0], "Data read by raid0_read is: \n", 256);
            user_panic("Data read by raid0_read is incorrect");
        }
    }
    writef("Your raid0 write & read are basically correct\n");
}