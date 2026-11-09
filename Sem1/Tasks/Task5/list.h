// list.h

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define BUFSIZE 1024
#define STRSIZE 16


typedef char **list;

extern jmp_buf begin;

void error(char *);
int listlen(list );
//void liststrreplace(char **);
void append(list *, char *);           
void deletelist(list *);                 
void lssort(list *);                    
void printlist(list );                   
int getsym();                               
int createlist(list *);                   

#endif //LIST_H
