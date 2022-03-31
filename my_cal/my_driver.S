#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>

.text

LEAF(_my_getchar) /*LEAF is defined in asm.h and LEAF functions don't call other functions*/
	
	loop_begin:
		lui s1, 0xb000
		lb t1, 0x00(s1)
		beq t1, zero, loop_begin
		nop
		
	sb t1, 0x00(s1)
	sb zero, 0x10(s1)
	move v0, t1
	jr ra
	
END(_my_getchar)            /*the function defined in asm.h*/

LEAF(_my_putchar)

	lui s1, 0xb000
	sb t1, 0x00(s1)
	sb zero, 0x10(s1)
	
END(_my_putchar)

LEAF(_my_exit)

	lui s1, 0xb000
	sb zero, 0x10(s1)
	
END(_my_exit)



