#ifndef MY_TAIL_H
#define MY_TAIL_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { N = 10 };

int getflag(char* str, int* pval, int* pflag);
int mytail(int argc, char* argv[]);

#endif // MY_TAIL_H
