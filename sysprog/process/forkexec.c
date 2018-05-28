// forkexec.c
//
// Calls fork and then the child calls exec with runs the calledbyexec.c program.
// This demonstrates the the parent and forked child will have different process ids,
// and the forked child and the exec'ed program will have the same process ids.
// In the case of the parent the code, data, and stack segments don't change, but
// in the case of the child, once it runs exec the code generated here in this
// file, along with the data and stack segements, are completely replaced by the 
// newly exec'ed program, therefore the child will never return to this program
// since this code has been completely replaced.
//
// Refer to:
//      calledbyexec.c - the program that is exec'ed by the child process
//      execprog.c - this also execs calledbyexec, but not from a fork
//      execself.c - a program that execs itself

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t childPid;
    int status = 0;

    // on success the process id of the child is returned to the parent
    // and zero is returned from the fork in the child (a call in the child
    // to getpid() will return its actual pid, not zero)
    switch (childPid = fork()) {
    case -1:
        printf("fork() error");
        exit(1);

    case 0:              // child comes here
        printf("ChildPid = %d\n", (int) getpid());
        argv[0] = "./calledbyexec";
        execvp("./calledbyexec", argv);
        break;

    default:             // parent comes here
        printf("ParentPid = %d\n", (int) getpid());
        wait(&status);           
        break;
    }

    // Only the parent will come here, since you never return from a successful exec

    exit(0);
}
