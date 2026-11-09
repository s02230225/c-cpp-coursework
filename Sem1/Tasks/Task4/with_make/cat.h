#ifndef MY_CAT_H
#define MY_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_LINE_LENGTH=1024 };

void print_file(FILE *file, int *number_lines, int *flag);
int mycat(int argc, char *argv[]);

#endif // MY_CAT_H