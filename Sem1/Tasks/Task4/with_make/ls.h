#ifndef MY_LS_H
#define MY_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

enum { MAX_LINE_LENGTH=1024 };

void printFileInfo(const char *path, const char *filename);
void listDirectory(const char *path, int longFormat, int showGroup);
void listDirectoryRecursive(const char *path, int longFormat, int showGroup);
int myls(int argc, char *argv[]);

#endif // MY_LS_H
