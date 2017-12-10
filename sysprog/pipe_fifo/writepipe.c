// writepipe.c
//
// Along with readpipe.c demonstrates using named pipes (referred to as FIFOs)
// This file (writepipe.c) creates the named pipe if it doesn't already exist
// (it might exist, since this can be run multiple times, and should be for 
// demo purposes).  It then writes a message to the named pipe (fifo).  Note
// that the open will block until a read from readpipe.c is performed, so
// in order to run this multiple times (to demonstrate multiple messages) this
// should be run in the background, i.e. './writepipe &' to free the terminal
// to run it again.
//
// Optionally, including any command line argument will cause the named pipes
// file to be removed.  Normally you don't want to do this, since you should
// rely on readpipe.c to remove it when it is done.
//
// Refer to:
//      readpipe.c - reads from the named pipe this write to

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "../commonlib/common.h"
#include "pipe.h"

int main(int argc, char *argv[]) {
    int fd;
    char buf[BUF_SIZE];
    char msg[30];


    // message to be sent
    sprintf(msg, "Hello, pipe! From pid: %d", (int) getpid());
    strcpy(buf, msg);

    // local header
    printf("\nWriting \"%s\" to named pipe\n", buf);

    // create named pipe (fifo)
    char *npipe="/tmp/npipe";
    if (mkfifo(npipe, 0664) == -1) {
        // errno EEXIST (already exists) is ok
        if (errno != EEXIST) {
            printf("%d\n", errno);
            die("mkfifo");
        }
    }

    // write to named pipe (fifo)
    printf("The open is blocking until pipe is read\n");
    if ((fd=open(npipe, O_WRONLY)) != -1) {
        if ((write(fd, buf, BUF_SIZE)) == -1)
            perror("write");
    }
    else
        perror("open");


    // close pipe and optionally delete it, although generally it is better
    // to let the readpipe.c delete it once it is done
    close(fd);
    // any command line arg will remove it.  Default of no args keeps it
    if (argc >= 2) {
        printf("\nPipe deleted because of command line argument\n");
        printf("The readpipe should normally do this\n");
        unlink(npipe);
    }
    return 0;
}
