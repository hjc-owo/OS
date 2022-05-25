#include "lib.h"
#include <mmu.h>
#include <env.h>
#define debug 0

static int pipeclose(struct Fd *);
static int piperead(struct Fd *fd, void *buf, u_int n, u_int offset);
static int pipestat(struct Fd *, struct Stat *);
static int pipewrite(struct Fd *fd, const void *buf, u_int n, u_int offset);

struct Dev devpipe = {
	.dev_id =	'p',
	.dev_name =	"pipe",
	.dev_read =	NULL,
	.dev_write = NULL,
	.dev_close = NULL,
	.dev_stat =	NULL,
};

#define BY2PIPE 32		// small to provoke races

struct Pipe {
	u_int p_rpos;		    // read position
	u_int p_wpos;		    // write position
	u_char p_buf[BY2PIPE];	// data buffer
};
