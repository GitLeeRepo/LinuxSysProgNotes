#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <signal.h>
#include "../commonlib/common.h"

static void signal_handler (int signo) {
    if (signo == SIGINT)
        printf("\b\bHandled: SIGINT (%d) - %s\n", signo, sys_siglist[signo]);
    else if (signo == SIGTERM)
        printf("Handled: SIGTERM (%d) - %s\n", signo, sys_siglist[signo]);
    else
        die("Unexpected signal\n");

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

    printf("\nRunning %s as pid: %d\n", argv[0], getpid());
    printf("Handles SIGINT (Ctrl-C or kill -s SIGINT <pid>) & SIGTERM (kill -s SIGTERM <pid>)\n"); 
    printf("In addition:\n"); // SIGHUP & SIGPROF messages

    if (signal (SIGINT, signal_handler) == SIG_ERR) 
        die("signal SIGINT");

    if (signal (SIGTERM, signal_handler) == SIG_ERR) 
        die("signal SIGINT");

    if (signal (SIGHUP, SIG_IGN) == SIG_ERR) 
        die("signal SIGINT");
    else
        printf("\tSIGHUP will be ignored\n");

    if (signal (SIGPROF, SIG_DFL) == SIG_ERR) 
        die("signal SIGINT");
    else
        printf("\tSIGPROF set to default which will terminate\n");

    while (1) {
        pause();
    }

    return (EXIT_SUCCESS);
}
