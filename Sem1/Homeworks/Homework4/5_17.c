/* 5.17 */
#include <stdio.h>
#include <stdlib.h>

enum {mas_count=3};

typedef float (*f1)(int);
typedef f1* (*f2)(void);

int main(){
    f2 *y[mas_count];
    return 0;
}