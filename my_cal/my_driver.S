#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>

.text

LEAF(_my_getchar) /*LEAF is defined in asm.h and LEAF functions don't call other functions*/
	

	li s2, 0
	li s3, 0
	li s4, 0
	li s5, 0
	
	loop_begin:
		lui s1, 0xb000
		lb t1, 0x00(s1)
		beq t1, zero, loop_begin
		nop
		
	sb t1, 0x00(s1)
	sb zero, 0x10(s1)
			
	
END(_my_getchar)            /*the function defined in asm.h*/

LEAF(_my_putchar)
	lb t1, 0x00(s1)
	sb t1, 0x00(s1)
	sb zero, 0x10(s1)
END(_my_putchar)

LEAF(_my_exit)
	sb zero, 0x10(s1)
END(_my_exit)



