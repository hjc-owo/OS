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

void mips_init()
{
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