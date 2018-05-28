// calledbyexec
//
// This very simple program is intended to be called by the execprog.c and 
// forkexec.c programs. One calls exec without fork and one calls it with fork.
// The thing to note when it is called is that it runs under the same process id
// as the process that called exec, which is the Unix standard for exec'ing new
// programs. In the case of forked exec it has the same pid as the calling program's
// forked child, and in the non-forked can it has the same pid as the calling program
// itself. 
// Once this program is exec'ed it will completely replace the code,
// data, and stack segments of the calling process (meaning you can never return to 
// the parent).  They will continue to share the same environment variables and
// file descriptors though.
//
// Refer to:
//      execprog.c - calls exec to run this program
//      forkexec.c - calls exec from child process to run this program
//      execself.c - a program that repeatedly exec's itself

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // note that this is the same pid as the program/process which
    // exec'ed this program
    printf("calledbyexec pid: %d\n", (int) getpid());

    for (int i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    return 0;
}
