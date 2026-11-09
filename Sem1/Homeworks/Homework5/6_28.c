/* 6.28 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node* list;
typedef struct Node {
    double* elem;
    list next;
    } Node;
typedef list* link;

void listpushl(double* elem, link lp){
    list cur=(list)calloc(1, sizeof(list));
    cur->elem=elem;
    cur->next=*lp;
    *lp=cur;
}

void listpushr(double* elem, link lp){
    if (*lp==NULL) listpushl(elem, lp);
    else{
        list cur=(list)calloc(1, sizeof(list));
        cur->elem=elem;
        list last=*lp;
        for(; last->next; last=last->next)
            {}
        last->next=cur;
    }
}

void listprint(list ls) {
    for (; ls; ls=ls->next)
        printf("%g ",  *(ls->elem));
    putchar('\n');
}

void listfree(link lp){
    list ls=*lp, q;
    while (ls!=NULL) {
        q=ls;
        ls=ls->next;
        free(q);
        }
    *lp=NULL;
} 

//////////////a
void svapfl(list ls){
    list first=ls;
    list last=ls;
    double* copy=NULL;
    for(; last->next; last=last->next)
        {}
    copy=first->elem;
    first->elem=last->elem;
    last->elem=copy;
}

////////////////b
void delfirstin(double* elem, link lp){
    list ls=*lp, copy=*lp;
    if (*(ls->elem)==*elem){
        *lp=copy->next;
        free(copy);
    }
    else{
        while (ls->next!=NULL){
            if  (*(ls->elem)==*elem){
                copy=ls->next;
                ls->next=copy->next;
                free(copy);
                return;
            }
            ls=ls->next;
        }
    }
}

////////////////c
void delallin(double* elem, link lp){
    list ls=(*lp)->next, copy=*lp;
    while (ls->next){
        if  (*(ls->next->elem)==*elem){
            copy=ls->next;
            ls->next=copy->next;
            free(copy);
        }
        else ls=ls->next;
    }
    if (*((*lp)->elem)==*elem){
        copy=*lp;
        *lp=copy->next;
        free(copy);
    }
}

//////////////d
void doubdoub(list ls){
    while (ls->next){
        list cur=(list)calloc(1, sizeof(list));
        cur->next=ls->next;
        cur->elem=ls->elem;
        ls->next=cur;
        ls=ls->next->next;
    }
    list cur=(list)calloc(1, sizeof(list));
    cur->next=NULL;
    cur->elem=ls->elem;
    ls->next=cur;
}

int main(){
    list l=NULL;
    double *a=calloc(1, sizeof(double));
    double *b=calloc(1, sizeof(double));
    double *c=calloc(1, sizeof(double));
    double *d=calloc(1, sizeof(double));
    *a=1; *b=2; *c=3; *d=4; 
    listpushr(a, &l);
    listpushr(b, &l);
    listpushr(c, &l);
    listpushr(d, &l);
    listprint(l);

    svapfl(l);
    listprint(l);

    delfirstin(d, &l);
    listprint(l);

    listpushr(a, &l);
    listpushr(b, &l);
    listpushr(c, &l);
    listprint(l);

    delallin(b, &l);
    listprint(l);

    doubdoub(l);
    listprint(l);

    listfree(&l);
    return 0;
} 