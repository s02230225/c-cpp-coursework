/* head.h */
#ifndef MY_WC_H
#define MY_WC_H

#include <stdio.h>
#include <stdlib.h>

void count_file(const char *filename, long *lines, long *words, long *chars);
int mywc(int argc, char *argv[]);

void print_help_echo();
void interpret_and_print(const char *str, int interpret);
int myecho(int argc, char *argv[]);


#endif // MY_WC_H