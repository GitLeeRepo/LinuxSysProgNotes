// multiprog.c
//
// Demonstate running multiple programs at the same time using the run in background '&' operator
// Run example: ./multiprog a &  ./multiprog b &  ./multiprog c &  ./multiprog d &
//              In this example run 4 instances each with a different letter for the command
//              line arg, with each instance running their own counter (in my runs they all
//              ended with the same count

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: multiprog <id letter a-z>\n");
        exit(1);
    }
    char *str = argv[1];
    for (int i = 1; i < 51; i++) {
        sleep(1);
        printf("%s: %d\n", str, i);
    }
    return 0;
}
