/* 3.48(a) */
#include <stdio.h>

int main(){
    int a=0;
    char c;
    do{
        c=getchar();
        if (c=='a') a++;
    } while(c!='.');
    printf("%d", a);
    return 0;
} 