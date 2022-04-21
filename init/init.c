#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <trap.h>

static void inverted_page_lookup_test(){
	struct Page *pp;
	page_alloc(&pp);
	Pde *pgdir = (Pde*)page2kva(pp);
	extern struct Page *pages;
	int a[10], len, i;
	page_insert(pgdir, pages + 2333, 0x23500000, 0);
	page_insert(pgdir, pages + 2333, 0x23400000, 0);
	page_insert(pgdir, pages + 2333, 0x23300000, 0);
	printf("%d\n", len = inverted_page_lookup(pgdir, pages + 2333, a));
	for(i = 0;i < len;i++) printf("%x\n", a[i]);
	page_remove(pgdir, 0x23400000);
	printf("%d\n", len = inverted_page_lookup(pgdir, pages + 2333, a));
	for(i = 0;i < len;i++) printf("%x\n", a[i]);
	page_insert(pgdir, pages + 2334, 0x23300000, 0);
	printf("%d\n", len = inverted_page_lookup(pgdir, pages + 2333, a));
	for(i = 0;i < len;i++) printf("%x\n", a[i]);
	printf("%d\n", len = inverted_page_lookup(pgdir, pages + 2334, a));
	for(i = 0;i < len;i++) printf("%x\n", a[i]);
}

void mips_init(){
	mips_detect_memory();
	mips_vm_init();
	page_init();

	inverted_page_lookup_test();

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

