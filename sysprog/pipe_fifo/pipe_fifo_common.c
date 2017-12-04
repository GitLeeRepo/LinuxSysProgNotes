// pipe_fifo_common.c
//
// Common functions for C files in the pipe_fifo directory.
// The C files that use this are demo/concept files that are intended to contain
// most of the program logic in the demo/concept C file itself with this common
// file only for support files not key to the concept being demonstrated.
// Each demo/concept type directory is self contained not needing any files
// other than standard library files that are not in the directory itself, with
// a Makefile included to build everything in that directory.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pipe.h"

void die(char *msg) {
    perror(msg);
    exit(5);
}

void info_die(char *msg) {
    puts(msg);
    exit(5);
}
