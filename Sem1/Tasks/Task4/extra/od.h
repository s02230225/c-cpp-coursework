#ifndef MY_OD_H
#define MY_OD_H
#include <errno.h>
#include <stdio.h>
#include <string.h>

enum { N = 10 };

int prtspec(char c, int flag);
int getflag(char* str, int* pflag);
int myod(int argc, char* argv[]);

#endif // MY_OD_H
