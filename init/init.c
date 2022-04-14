#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <trap.h>

static void buddy_test(){
	u_int pa_1, pa_2;
	u_char pi_1, pi_2;
	buddy_alloc(1572864, &pa_1, &pi_1);
	buddy_alloc(1048576, &pa_2, &pi_2);
	printf("%x\n%d\n%x\n%d\n", pa_1, (int)pi_1, pa_2, (int)pi_2);
	buddy_free(pa_1);
	buddy_free(pa_2);
}
void mips_init(){
	mips_detect_memory();
	mips_vm_init();
	page_init();
	buddy_init();
	buddy_test();
	*((volatile char*)(0xB0000010)) = 0;
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

