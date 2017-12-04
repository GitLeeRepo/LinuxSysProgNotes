// readpipe.c
//
// Along with writepipe.c demonstrates using named pipes (referred to as FIFOs)
// This file (readpipe.c) reads from the named pipe (fifo) that writepipe.c
// has written to, possibly multiple times under different process ids.
// It reads from within a loop and will remain blocking until interrupted
// with Ctrl-C for which a handler is provided here, in order to ensure
// the pipe is closed and removed. 
//
// Optionally, including any command line argument will open this in unblocking
// mode, which should allow the program to complete without the Ctrl-C interrupt,
// but it currently isn't working as intended.  The option is left here to
// try and get this to work, or at least understand better why it isn't working. 
//
// Refer to:
//      writepipe.c - writes to the named pipe this reads from

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include "pipe.h"

// global so it is visble to signal event handler
static int fd;
static char *npipe="/tmp/npipe"; // named pipe to read from

// SIGINT (Ctrl-C) handler
static void sigint_handler(int signo) {
    char *sigStr = "(SIGINT)";

    if (signo != 2)
        sigStr[0] = '\0';
        
    // printf not always good idea in reentrant code, but ok here
    printf("\b\bDone! Received signal number: %d %s\n", signo, sigStr);

    close(fd);
    unlink(npipe);
    exit(0);
}

int main(int argc, char *argv[]) {
    char buf[BUF_SIZE];

    // set up SIGINT (Ctrl-C) handler
    if (signal (SIGINT, sigint_handler) == SIG_ERR) 
        die("Signal Error");

    printf("Reading from named pipe on client pid: %d\n", (int) getpid());
    printf("Press Ctrl-C to end\n");

    // open named pipe (fifo)
    // any arg will open non-blocking, default no arg is blocking (recommended)
    if (argc >= 2)
        fd=open(npipe, O_RDWR | O_NONBLOCK); // currently not working as intended 
    else
        fd=open(npipe, O_RDWR); 

    // check for open error
    if (fd < 1) 
        die("open");
    
    // read from named pipe (fifo)
    ssize_t rslt;
    while ((rslt = read(fd, buf, BUF_SIZE)) > 0) {
        printf("Read %d from pipe: %s\n", (int) rslt, buf);
    }

    if (rslt == -1) 
        perror("read");
    else
        printf("Done!\n");

    // close and remove named pipe (fifo)
    close(fd);
    unlink(npipe);

    return 0;
}
