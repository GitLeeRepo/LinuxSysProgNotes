
// execself.c
//
// This program exec's itself a number between the first arg and MAX_RUNS times
// Each exec completely wipes out prior instances code, data, and stack segments
// with the new instance getting its own.  Therefore they don't share any state
// between instances using these segements (although you could use environment
// variables, or the file system).  This program is able to communicate the state 
// between each instance by passing an increment integer value for the first 
// command line arguement.  Once this value exceeds the MAX_RUNS the last instance
// will terminate by not exec'ing another instance.
//  
// One thing to note though is that each instance of the program is running under 
// the same process id, which is the Unix standard for exec'ing processes.  To create 
// a new process the parent must do a fork() call first. 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const int MAX_RUNS = 10;
    const char *msg = "provide at least one argument, the first argument must be an integer > 1 and <= %d\n";

    if (argc < 1) {
        printf(msg, MAX_RUNS);
        exit(1);
    }

    int arg1 = atoi(argv[1]);
    if (arg1 < 1 || arg1 > MAX_RUNS) {
        printf(msg, MAX_RUNS);
        exit(1);
    }

    // we will note that the pid is the same as the parent for each instance
    printf("execself pid: %d\n", (int) getpid());

    int i;
    for (i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
        sleep(1);
    }
   
    // increment the first argument by 1 
    char tmp[10];
    sprintf(tmp, "%d", ++arg1);
    argv[1] = tmp;

    // as long as this has been called < MAX_RUNS exec ourselves
    // the first argument will control how many times a new instance
    // is exec'ed 
    if (arg1 <= MAX_RUNS)
        execvp("./execself", argv);

    printf("This is run on the last insance only\n"); 
}
