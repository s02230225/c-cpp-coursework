#ifndef MY_MV_H
#define MY_MV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

enum { MAX_LINE_LENGTH=1024 };
int copy_permissions(const char *src, const char *dest);
int move(const char *old_file, const char *new_file);
int mymv(int argc, char *argv[]);

#endif // MY_MV_H
