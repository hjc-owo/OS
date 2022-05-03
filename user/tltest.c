#include "lib.h"

void umain() {
    writef(
        "Smashing some kernel codes...\n"
        "If your implementation is correct, you may see some TOO LOW here:\n"
    );
    *(int *) KERNBASE = 0;
    writef("My mission completed!\n");
}
