// copybetter.c
// modified version of the copy.c program in "The Linux Programming Interface"
// by Michael Kerrisk.
//
// This program is a much more robust version of a copy file program than is 
// the simple copysimple.c program.  This version uses command line args,
// does better error checking, and uses a buffer instead of copying a single
// character at a time.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "fileio.h"

#ifndef BUF_SIZE        // Allow "cc -D" to override definition 
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // Evaluate command line arguements
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        info_die("usage: copy old-file new-file");

    // Open input file
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        die("opening input file");

    // setup flags and permissions for the new ouput file
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */

    // Open output file
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        die("opening output file");

    // read from input file and write to output file
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
        if (write(outputFd, buf, numRead) != numRead)
            die("couldn't write whole buffer");

    if (numRead == -1)
        die("read");

    // close files
    if (close(inputFd) == -1)
        die("close input");
    if (close(outputFd) == -1)
        die("close output");

    exit(EXIT_SUCCESS);
}

