#include "lib.h"


void umain()
{
	
    int i=0;
	char buf[32] = {0};
	char c = 0;
	u_int cons = 0x10000000;
	writef("console test, please input a string:\n");
	while(1){
		syscall_read_dev(&c, cons, 1);
		if(c == '\r')
			break;
		if(c != 0){
			buf[i++] = c;	
		}
	}
	buf[i++] = '\n';
	syscall_write_dev(buf, cons, i);
	writef("end of devtst\n");
	
	writef("IDE test\n");
	if(syscall_read_dev(&c, 0x0fffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x10000020, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x1000001f, 8) != -3)
		user_panic("failed dev address test");

	if(syscall_read_dev(&c, 0x12ffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x13004200, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x130041ff, 8) != -3)
		user_panic("failed dev address test");

	if(syscall_read_dev(&c, 0x14ffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x15000200, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_read_dev(&c, 0x150001ff, 8) != -3)
		user_panic("failed dev address test");
	
	if(syscall_write_dev(&c, 0x0fffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x10000020, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x1000001f, 8) != -3)
		user_panic("failed dev address test");

	if(syscall_write_dev(&c, 0x12ffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x13004200, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x130041ff, 8) != -3)
		user_panic("failed dev address test");

	if(syscall_write_dev(&c, 0x14ffffff, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x15000200, 1) != -3)
		user_panic("failed dev address test");
	if(syscall_write_dev(&c, 0x150001ff, 8) != -3)
		user_panic("failed dev address test");

	writef("dev address is ok\n");
		
        while (1) {
		;
        }
}


