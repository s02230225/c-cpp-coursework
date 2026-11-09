#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum { SIZE = 16 };

typedef struct {
        int c;
        void* term;
        
        char** lst;
        int sizelist;
        int curlist;
        
        char* buf;
        int sizebuf;
        int curbuf;
        
        char* rb;
        int sizerb;
        int currb;
} state;

void err(state* st);
void null_list(state* st);
void nullbuf(state* st);
void nullrb(state* st);
int isspec(int c);
int symset(int c);
int iscorr(int c);
void printlist(state* st);
void clearlist(state* st);
int getsym(state* st);
void addsym(state* st);
void addword(state* st);
void termlist(state* st);
void bubble_sort(state* st);
void outst(state* st);
#endif // PARSER_H