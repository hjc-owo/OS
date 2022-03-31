/*
 * Copyright (C) 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <printf.h>
#include <pmap.h>

struct my_struct {
	int size;
	char c;
	int array[5];
};

int main()
{
	struct my_struct t1;
	t1.size = 5; 
	t1.c = 'b';
   	t1.array[0] = 0;
   	t1.array[1] = -11111111;
   	t1.array[2] = 22222222;
    t1.array[3] = -5;
	t1.array[4] = 2;	
	printf("main.c:\tmain is start ...\n");
	printf("%-5T", &t1);

	mips_init();
	panic("main is over is error!");

	return 0;
}
