#ifndef SHLFUNC_H
#define SHLFUNC_H

#include "list.h"
#include "tree.h"
#include "isword.h"
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>

extern jmp_buf sexit;
static int last_pid;

int endofshell();
void shellexit();
int pwd();
void print_last_pid();
void shellcd(char *dirpath);
void _changein(tree t);
void _changeout(tree t);
void changeinout(tree t);
int progrun(tree t, int flag);
int convwork(tree t, int flag);
int shellwork(tree t);

#endif //SHLFUNC_H