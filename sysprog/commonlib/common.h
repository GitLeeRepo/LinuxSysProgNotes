// common.h
//
// header file for common.c


// #define DEBUG on the command line, either in makefile or gcc -DDEBUG 
#ifdef DEBUG
#define DBG(fmt, args...) printf("%s:%s:%d "fmt, __FILE__, __FUNCTION__, __LINE__, args)
#else
#define DBG(fmt, args...) 
#endif


#ifndef COMMON_H
#define COMMON_H

void die(char *msg);
void info_die(char *msg); 
int addCommas_ul(char  *commaNumStr, unsigned long ulNum);
int maxIntAr(int *ar, int numElements);
int minIntAr(int *ar, int numElements);
int checkDupeIntAr(int *ar, int numElements, int *dupeNum);

#endif
