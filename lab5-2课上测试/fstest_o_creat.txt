#include "lib.h"


void umain()
{
    int fdnum;
    char buf[200];
    fdnum = open("/created_file", O_RDWR|O_CREAT);
    fwritef(fdnum, "test create");
    close(fdnum);
    fdnum = open("/created_file", O_RDWR);
    read(fdnum, buf, 150);
    writef("read from new file: %s\n", buf);
    while(1);
}

/* expected output:
==================================================================
read from new file: test create
==================================================================
*/
