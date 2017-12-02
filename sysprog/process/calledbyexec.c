// calledbyexec
//
// This very simple program is intended to be called by the execprog.c program.
// The thing to note when it is called is that it runs under the same process id
// as the parent that called exec, which is the Unix standard for exec'ing new
// programs.  Once this program is exec'ed it will completely replace the code,
// data, and stack segments of the parent (meaning you can never return to the 
// parent).  They will continue to share the same environment variables and
// file descriptors though.
//
// Refer to:
//      execprog.c - calls exec to run this program
//      execself.c - a program that repeatedly exec's itself

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // note that this is the same pid as the program which
    // exec'ed this program
    printf("calledbyexec pid: %d\n", (int) getpid());

    int i;
    for (i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    return 0;
}
