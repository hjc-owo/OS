#include "lib.h"

#define tot 30

#define uassert(cond) { \
    if (!(cond)) { \
        writef("%s: assertion failed in %x at line %d\n", __FILE__, env->env_id, __LINE__); \
        syscall_panic("os test failed"); \
    } \
}

#define accepted(...) syscall_panic("Accepted!")
