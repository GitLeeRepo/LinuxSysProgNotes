// dispenv.c
//
// Display a list of enviroment variables using the C run-time 'environ' global variable
// Also, shows the use of getenv() to display the value of a specific enviroment variable.

#include <stdio.h>
#include <stdlib.h>

// C run-time defines 'environ' as a pointer to a list of environment variables (null terminated strings)
// similar to argv
extern char **environ; 

int main(int argc, char *argv[])
{
    char **ep; // pointer to walk through the list of environment variables

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    // use getenv() to display the value of the 'SHELL' environment variable
    printf("\n\nUsing getenv() to return value of 'SHELL': %s\n", getenv("SHELL"));
    exit(0);
}
