#include "lib.h"
#include <mmu.h>

static int cons_read(struct Fd *, void *, u_int, u_int);
static int cons_write(struct Fd *, const void *, u_int, u_int);
static int cons_close(struct Fd *);
static int cons_stat(struct Fd *, struct Stat *);

struct Dev devcons = {
	.dev_id =	'c',
	.dev_name =	"cons",
	.dev_read =	NULL,
	.dev_write =	NULL,
	.dev_close =	NULL,
	.dev_stat =	NULL,
};
