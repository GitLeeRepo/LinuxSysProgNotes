// readstdin.c
// 
// Uses STDIN_FILENO to read from the console using the read() function
//
// Example usage: echo "test" | ./rstdio

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 120

int main() {
    char buffer[MAX_BUF+1];
    ssize_t numRead;

    numRead = read(STDIN_FILENO, buffer, MAX_BUF);
    if (numRead == -1)
        exit(0);

    buffer[numRead] = '\0';
    printf("The input data was %d characters long and the input was: %s\n", (int) numRead, buffer);
}
