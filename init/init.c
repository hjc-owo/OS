#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <kclock.h>
#include <trap.h>

extern u_int test1(char *p, u_int offset);

extern u_int test2(char *p, u_int offset);

void test() {
    char a[100] = {5, 4, 3, 2, 1};
    int i = 0;
    // lw -> lh
    i = test1(a, 2);
    printf("%08x\n", i);
    // lh -> lb
    i = test1(a, 3);
    printf("%08x\n", i);
    // lw -> lb
    i = test2(a, 1);
    printf("%08x\n", i);
}

void mips_init() {
    printf("init.c:\tmips_init() is called\n");
    mips_detect_memory();

    mips_vm_init();
    page_init();

    env_init();

    trap_init();
    kclock_init();
    test();
    *((volatile char *) 0xB0000010);
}

void bcopy(const void *src, void *dst, size_t len) {
    void *max;

    max = dst + len;
    // copy machine words while possible
    while (dst + 3 < max) {
        *(int *) dst = *(int *) src;
        dst += 4;
        src += 4;
    }
    // finish remaining 0-3 bytes
    while (dst < max) {
        *(char *) dst = *(char *) src;
        dst += 1;
        src += 1;
    }
}

void bzero(void *b, size_t len) {
    void *max;

    max = b + len;

    //printf("init.c:\tzero from %x to %x\n",(int)b,(int)max);

    // zero machine words while possible

    while (b + 3 < max) {
        *(int *) b = 0;
        b += 4;
    }

    // finish remaining 0-3 bytes
    while (b < max) {
        *(char *) b++ = 0;
    }

}
