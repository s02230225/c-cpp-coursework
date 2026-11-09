/* 5.16 */
#include <stdio.h>
#include <stdlib.h>

enum {mas_count=3};

typedef double* (*f)(int, int);
 
int main(){
    f x[mas_count];
    return 0;
}