#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <trap.h>

static void page_protect_test() {
    extern struct Page *pages;
    struct Page *pp;
    printf("%d\n", page_protect(pages + 16383));
    printf("%d\n", page_protect(pages + 16383));
    page_alloc(&pp), pp->pp_ref++;
    printf("%d\n", page2ppn(pp));
    printf("%d\n", page_protect(pp));
    printf("%d\n", page_status_query(pp));
    printf("%d\n", page_status_query(pages + 16383));
    printf("%d\n", page_status_query(pages + 16381));
    page_decref(pp);
    printf("%d\n", page_status_query(pp));
}

void mips_init() {
    mips_detect_memory();
    mips_vm_init();
    page_init();
    page_protect_test();
    *((volatile char *) (0xB0000010)) = 0;
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

