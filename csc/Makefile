all:
	gcc ./code/fibo.c -o ./code/fibo.o -include<./include/fibo.h>
	gcc ./code/main.c -o ./code/main.o
	gcc ./code/fibo.o ./code/main.o -o fibo


clean:
	rm ./code/fibo.o
	rm ./code/main.o
	
