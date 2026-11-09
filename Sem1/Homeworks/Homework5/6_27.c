/* 6.27 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node* list;
typedef struct Node {
    int elem;
    list next;
    } Node;
typedef list* link;

void listpushl(int elem, link lp){
    list cur=(list)calloc(1, sizeof(list));
    cur->elem=elem;
    cur->next=*lp;
    *lp=cur;
}

void listpushr(int elem, link lp){
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
        printf("%d ",  ls->elem);
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

int listmin(list ls){
    int n=INT_MAX;
    for (; ls; ls=ls->next)
        if (ls->elem<n) n=ls->elem;
    return n;
}

/////////////////////a
int listsum(list ls){
    int n=0;
    for (; ls; ls=ls->next)
        n+=ls->elem;
    return n;
}

/////////////////////b
int listmax(list ls){
    int n=INT_MIN;
    for (; ls; ls=ls->next)
        if (ls->elem>n) n=ls->elem;
    return n;
}

////////////////////c
int listordered(list ls){
    if (ls->next==NULL) return 1;
    else{
        for (; ls->next; ls=ls->next)
            if (ls->elem>=ls->next->elem) return 0;
        return 1;
    }
}

////////////////////d
int listsummaxandmin(list ls){
    return listmax(ls)+listmin(ls);
}

int main(){
    list a=NULL;
    listpushr(1, &a);
    listpushr(2, &a);
    listpushr(3, &a);
    listpushr(4, &a);
    listprint(a);
    printf("%d\n", listsum(a));
    printf("%d\n", listmax(a));
    printf("%s\n", (listordered(a)) ? "yes" : "no");
    printf("%d\n", listsummaxandmin(a));
    listfree(&a);
    return 0;
} 