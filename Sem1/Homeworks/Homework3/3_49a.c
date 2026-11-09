/* 3.49(a) */
#include <stdio.h>

int main(){
    char c;
    do {
        c=getchar();
        if (c=='?') putchar('!');
        else printf("%c", c);
    } while(c!='.');
} 