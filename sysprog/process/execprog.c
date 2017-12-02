// execproc.c
//
// This program prints its process id and arguements and then calls exec to
// run another program 'calledbyexec.c' which will completely wipe out this
// current programs code, data, and stack segments replacing it all with the
// new running program, although they will continue to share the same environment
// variables and file descriptors.
// 
// The thing to note when it is that the new program runs under the same process id
// as this program.
//
// Refer to:
//      calledbyexec.c - the new program that is exec'ed by this program
//      execself.c - a program that repeatedly exec's itself

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Note that the pid will stay the same once the new program loaded
    printf("execprog pid: %d\n", (int) getpid());

    // print out the command line args
    int i;
    for (i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // replace argv program name (not required) and exec the new program passing
    // on the command line arguements of this program (with the modified prog name)
    argv[0] = "./calledbyexec";
    execvp("./calledbyexec", argv);

    // never gets here
    printf("This will never run since the code gets swapped out before getting here\n"); 
}
