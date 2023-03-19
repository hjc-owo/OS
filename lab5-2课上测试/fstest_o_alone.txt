#include "lib.h"


void umain()
{
    int r, fdnum, n;
    char buf[200];
    fdnum = open("/newmotd", O_RDWR | O_ALONE);
    if ((r = fork()) == 0) {
	    n = read(fdnum, buf, 5);
	    writef("[child] buffer is \'%s\'\n", buf);
    } else {
	    n = read(fdnum, buf, 5);
	    writef("[father] buffer is \'%s\'\n", buf);
    }
    while(1);
}

/* expected output:
==================================================================
[father] buffer is 'This '
[child] buffer is 'This '
==================================================================
*/
