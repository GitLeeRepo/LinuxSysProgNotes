// virtmem.c
//
// Demo vitual memory
// This type of program used to work as a good demonstration of virtual memory, because you
// could run multiple instances and each would show the same memory address for the allocated
// memory, and yet not overwrite each other (because the memory was virtual and not an actual
// physical address).  But these days the os randomizes the start address to help guard against 
// malicious attacks attacking specific memory addresses in vitual user space of known code/data
//
// To run multiple instances: ./virtmem & ./virtmem &

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int)); // a1
    assert(p != NULL);

    // count up if pid is even, down if not.  Since the 2nd pid tends to be 1 greater than
    // the 1st one this tends to workout, but no guarantee
    *p = ((getpid() %2) ? 1 : 20);

    printf("\n");
    int i;
    for (i = 1; i < 21; i++) {
        sleep(1);
        printf("pid: (%d); address pointed to by p: %p; p value (alloc on heap): %d\n", getpid(), p, *p);

        // count up if pid even, count down if odd
        *p = ((getpid() % 2) ? *p + 1 : *p - 1);
    }
    printf("Done: hit return\n");
    return 0;
}
