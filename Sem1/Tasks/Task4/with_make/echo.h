#ifndef MY_ECHO_H
#define MY_ECHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_help_echo();
void interpret_and_print(const char *str, int interpret);
int myecho(int argc, char *argv[]);

#endif // MY_ECHO_H