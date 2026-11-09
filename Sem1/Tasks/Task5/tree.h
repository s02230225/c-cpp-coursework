#ifndef TREE_H
#define TREE_H

#include "list.h"
#include "isword.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

enum type_of_next{
    NXT, AND, OR   
};

struct cmd_inf {
    char ** argv;
    char *infile;
    char *outfile;
    int append;
    int backgrnd;
    struct cmd_inf* psubcmd;
    struct cmd_inf* pipe;
    struct cmd_inf* next;
    enum type_of_next type;
};

typedef struct cmd_inf *tree;
typedef struct cmd_inf node;



void make_shift(int);
void print_argv(char **,int);
int print_tree(tree, int);
tree maketree();
tree simplecommand(list *);
tree conveyer(list *);
tree andor(list *);
tree nexttree(list *);
void modifinout(tree, list *);
tree buildtree(list *);
tree buildsubshell(tree, list *);
void delete_tree(tree *);

#endif //TREE_H