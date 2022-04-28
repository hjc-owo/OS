#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <kclock.h>
#include <trap.h>

void pv_check() {
	S_init(1, 1);
	S_init(2, 1);
	struct Env* e1, *e2, *e3;
    envid2env(my_env_create(), &e1, 0);
	envid2env(my_env_create(), &e2, 0);
	envid2env(my_env_create(), &e3, 0);
	printf("%d\n", P(e1, 1));
	printf("envid: %d, status: %d\n", e1->env_id, get_status(e1));
	printf("%d\n", P(e2, 1));
	printf("envid: %d, status: %d\n", e2->env_id, get_status(e2));
	printf("%d\n", P(e3, 1));
	printf("%d\n", P(e3, 2));
	printf("envid: %d, status: %d\n", e3->env_id, get_status(e3));
	printf("%d\n", P(e1, 2));
	printf("%d\n", V(e1, 1));
	printf("%d\n", V(e1, 2));
	printf("envid: %d, status: %d\n", e1->env_id, get_status(e1));
}

void mips_init()
{
	mips_detect_memory();
	mips_vm_init();
	page_init();
	env_init();
	
	pv_check(); // for lab3-1-Extra local test

	*((volatile char*)(0xB0000010)) = 0;
}

void bcopy(const void *src, void *dst, size_t len)
{
	void *max;

	max = dst + len;
	// copy machine words while possible
	while (dst + 3 < max)
	{
		*(int *)dst = *(int *)src;
		dst+=4;
		src+=4;
	}
	// finish remaining 0-3 bytes
	while (dst < max)
	{
		*(char *)dst = *(char *)src;
		dst+=1;
		src+=1;
	}
}

void bzero(void *b, size_t len)
{
	void *max;

	max = b + len;
	
	// zero machine words while possible

	while (b + 3 < max)
	{
		*(int *)b = 0;
		b+=4;
	}
	
	// finish remaining 0-3 bytes
	while (b < max)
	{
		*(char *)b++ = 0;
	}		
	
}



