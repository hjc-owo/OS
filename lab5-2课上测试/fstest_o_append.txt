#include "lib.h"


void umain()
{
    int r, fdnum, n;
    char buf[200];
    if ((r = open("/newmotd", O_RDWR | O_APPEND) < 0)) {
	    user_panic("open /motd: %d\n", r);
    }
    fdnum = r;
    if (r = fwritef(fdnum, "test append") < 0) {
	    user_panic("fwritef %d\n", r);
    }
    close(fdnum);
    if ((r = open("/newmotd", O_RDWR) < 0)) {
	    user_panic("open /motd: %d\n", r);
    }
    fdnum = r;
    if ((n = read(fdnum, buf, 150)) < 0) {
	    writef("read %d\n", n);
	    return;
    }
    close(fdnum);
    writef("\n%s\n", buf);
    while (1);
}

/* expected output:
==================================================================
This is a different massage of the day!
test append
==================================================================
*/
