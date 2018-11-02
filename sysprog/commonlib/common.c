// common.c
//
// Common functions for C files related repositories and other directories.
// This common.c should be stored in the C_ProgrammingNotes repository, with
// instructions in the other repositories to access this file.
//.
// The C files that use this are demo/concept files that are intended to contain
// most of the program logic in the demo/concept C file itself with this common
// file only for support files not key to the concept being demonstrated.
// Each demo/concept type directory is self contained not needing any files
// other than standard library files that are not in the directory itself, with
// a Makefile included to build everything in that directory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "common.h"

void die(char *msg) {
    perror(msg);
    exit(5);
}

void info_die(char *msg) {
    puts(msg);
    exit(5);
}

// add commas to a string from the unsigned long pased in
int addCommas_ul(char  *commaNumStr, unsigned long ulNum) {
    char  temp[30];  // buffer to hold the orig num as a string without the commas
    
    // zero out the temp buffer and the commaNumStr begin copied to
    memset(temp, 0, 30); 
    memset(commaNumStr, 0, 30); 

    // convert the number to a string
    sprintf(temp, "%lu", ulNum);

    // the length of the number, used to determine comma positions
    int numlen = strlen(temp);

    int adjust = ((numlen % 3 == 0) ? 0 : 1); // adjustment starting pos of the new string
    int j = numlen + (numlen/3) + adjust; // used to index the new string
    int k = -1; // used to position the commas
    for (int i = numlen; i >= 0; i--) {
        if ((k+0) % 3 == 0) {
            if ((k) != 0)
                commaNumStr[j] = ',';
            j--;
        }
        commaNumStr[j--] = temp[i];
        k++;
    }
    return numlen;
}


int maxIntAr(int *ar, int numElements) {
    int max = 0;

    for (int i = 0; i < numElements; i++) {
        if (ar[i] > max)
            max = ar[i];
    }
    return max;
}

int minIntAr(int *ar, int numElements) {
    int min = INT_MAX;

    for (int i = 0; i < numElements; i++) {
        if (ar[i] < min)
            min = ar[i];
    }
    return min;
}

int checkDupeIntAr(int *ar, int numElements, int *dupeNum) {
    int count = 0;
    *dupeNum = 0;

    for (int i = 0; i < numElements; i++) {
        count = 0;
        for (int j = 0;  j < numElements; j++) {
            if (ar[i] == ar[j]) 
                count++;
            if (count == 2) {
                *dupeNum = ar[i];
                return 1; // yes dupes
            }
        } 
    }
    return 0; // no dupes
}
