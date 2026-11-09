/* head.h */
#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

enum { MAX_LINE_LENGTH=1024 };

void printFileInfo(const char *path, const char *filename);
void listDirectory(const char *path, int longFormat, int showGroup);
void listDirectoryRecursive(const char *path, int longFormat, int showGroup);
int myls(int argc, char *argv[]);

void print_file(FILE *file, int *number_lines);
int mycat(int argc, char *argv[]);

void count_file(const char *filename, long *lines, long *words, long *chars);
int mywc(int argc, char *argv[]);

void print_help_echo();
void interpret_and_print(const char *str, int interpret);
int myecho(int argc, char *argv[]);

void copy_permissions(const char *src, const char *dest);
void move(const char *old_file, const char *new_file);
int mymv(int argc, char *argv[]);

int mypwd();

#endif // MY_FUNCTIONS_H