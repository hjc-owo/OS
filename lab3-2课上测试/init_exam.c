void mips_init()
{
	printf("init.c:\tmips_init() is called\n");
	mips_detect_memory();
	
	mips_vm_init();
	page_init();
	
	env_init();
    
    // for lab3-2-exam local test
    ENV_CREATE_PRIORITY(user_A, 2);
    ENV_CREATE_PRIORITY(user_B, 1);	

	trap_init();
	kclock_init();
	panic("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	while(1);
	panic("init.c:\tend of mips_init() reached!");
}
