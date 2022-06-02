INCLUDES = -I../include/

USERLIB := printf.o \
		print.o \
		libos.o \
		fork.o \
		pgfault.o \
		syscall_lib.o \
		ipc.o \
		string.o \
		fd.o \
		pageref.o \
		file.o \
		pipe.o \
		fsipc.o \
		wait.o \
		spawn.o \
		console.o \
		fprintf.o

CFLAGS += -nostdlib -static

all: echo.x echo.b num.x num.b testptelibrary.b testptelibrary.x testarg.b testpipe.x testpiperace.x icode.x init.b sh.b cat.b ls.b\
	devtst.x devtst.b tltest.x tltest.b fktest.x fktest.b pingpong.x pingpong.b idle.x fstest.x fstest.b $(USERLIB) entry.o syscall_wrap.o

%.x: %.b.c 
	echo cc1 $< 
	$(CC) $(CFLAGS) -c -o $@ $<

%.b.c: %.b
	echo create $@
	echo bintoc $* $< > $@~
	chmod +x ./bintoc
	./bintoc $* $< > $@~ && mv -f $@~ $@
	
%.b: entry.o syscall_wrap.o %.o $(USERLIB)
	echo ld $@
	$(LD) -o $@ $(LDFLAGS) -G 0 -static -n -nostdlib -T ./user.lds $^

%.o: %.c
	echo user1 cc $<
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: %.S
	echo as $<
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: lib.h

.PHONY: clean

clean:
	rm -rf *~ *.o *.b.c *.x *.b

include ../include.mk
