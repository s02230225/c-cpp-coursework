/* int list */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node* list;
typedef struct Node {
    int elem;
    list next;
    } Node;
typedef list* link;

void listprint(list ls) {
    for (; ls; ls=ls->next)
        printf("%d ",  ls->elem);
    putchar('\n');
}

int listlen(list ls){
    int n=0;
    for (; ls; ls=ls->next)
        n++;
    return n;
}

void listpushl(int elem, link lp){
    list cur=(list)calloc(1, sizeof(list));
    cur->elem=elem;
    cur->next=*lp;
    *lp=cur;
}

int listpopl(link lp){
    list ls=*lp, q;
    int ret=0;
    if (ls==NULL){
        fprintf(stderr, "Delite item from empty list");
        return 0;
    }
    else{
        q=ls;
        ret=ls->elem;
        *lp=ls->next;
        free(q);
        return ret;
    }
}

int listpopr(link lp){
    list ls=*lp, q;
    int ret=0;
    if (ls==NULL){
        fprintf(stderr, "Delite item from empty list");
        return 0;
    }
    else if (ls->next==NULL) return listpopl(lp);
    else{
        q=ls;
        while (ls->next){
            q=ls;
            ls=ls->next;
        }
        q->next=NULL;
        q=ls;
        ret=ls->elem;
        free(q);
        return ret;
    }
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

void listfree(link lp){
    list ls=*lp, q;
    while (ls!=NULL) {
        q=ls;
        ls=ls->next;
        free(q);
        }
    *lp=NULL;
} 

int listcount(int elem, list ls){
    int n=0;
    for (; ls; ls=ls->next)
        if (ls->elem==elem) n++;
    return n;
}

int listmax(list ls){
    int n=INT_MIN;
    for (; ls; ls=ls->next)
        if (ls->elem>n) n=ls->elem;
    return n;
}

int listmin(list ls){
    int n=INT_MAX;
    for (; ls; ls=ls->next)
        if (ls->elem<n) n=ls->elem;
    return n;
}

list listindexl(int elem, list ls){
    for (; ls; ls=ls->next)
        if (ls->elem==elem) return ls;
    return NULL;
}

list listindexr(int elem, list ls){
    list last=NULL;
    for (; ls; ls=ls->next)
        if (ls->elem==elem) last=ls;
    return last;
}
/* dont work
void listdelindex(link lp, list ls){
    if (*lp==ls) listpopl(lp);
    else{
        list thisls=*lp;
        while (thisls->next!=ls && ls->next)
            thisls=thisls->next;
        if (thisls->next==ls && ls->next==NULL);
        else if (thisls->next==ls && ls->next!=NULL) ...
    }
}
*/

int main(){
    list a=NULL;
    /* example */
    listpushr(1, &a);
    listpushr(2, &a);
    listpushr(3, &a);
    listpushr(4, &a);
    listprint(a);
    printf("%d\n", listindexl(3, a)->next->elem);
    listpushr(3, &a);
    listpushr(2, &a);
    printf("%d\n", listindexr(3, a)->next->elem);
    /* end of example */
    listfree(&a);
    return 0;
} 