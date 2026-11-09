#ifndef MY_GREP_H
#define MY_GREP_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getflag(char* str, int* pflag);
int mygrep(int argc, char* argv[]);

#endif // MY_GREP_H
