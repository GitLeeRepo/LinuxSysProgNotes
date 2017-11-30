// simplefork.c
//
// Demonstrates that even though the child receives a copy of its parent's data
// and stack segments, they are separate.  Therefore they show different values
// for the same variables after the child makes changes to them.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int inDataSeg = 100;  

int main(int argc, char *argv[]) {
    int inStackSeg = 400; 
    pid_t childPid;

    // on success the process id of the child is returned to the parent
    // and zero is returned from the fork in the child (a call in the child
    // to getpid() will return its actual pid, not zero)
    switch (childPid = fork()) {
    case -1:
        printf("fork() error");
        exit(1);

    case 0:              // child comes here
        inDataSeg *= 2;
        inStackSeg *= 2;
        break;

    default:             // parent comes here
        sleep(3);           
        break;
    }

    // Both parent and child come here
    // the condition varies the labeling between child and parent
    printf("PID=%ld %s inDataSeg=%d inStackSeg=%d\n", (long) getpid(),
            (childPid == 0) ? "(child) " : "(parent)", inDataSeg, inStackSeg);

    exit(0);
}
