#include "lib.h"


void umain()
{
    int fdnum;
    char buf[512];
    list_dir("/", buf);
    writef("dir of / : %s\n", buf);
    fdnum = open("/created_file", O_RDWR|O_CREAT);
    close(fdnum);
    list_dir("/", buf);
    writef("dir of / : %s\n", buf);
    while(1);
}

/* expected output: (with O_CREAT implemented)
==================================================================
dir of / : motd newmotd
dir of / : motd newmotd created_file
==================================================================
*/
