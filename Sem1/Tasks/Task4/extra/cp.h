#ifndef MY_CP_H
#define MY_CP_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int cpfile(char* arg1, char* arg2);
int mycp(int argc, char* argv[]);

#endif // MY_CP_H
