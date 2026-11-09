/* 2.26 */
#include <stdio.h>

int main(){
    char a;
    unsigned int b;
    scanf("%u", &b);
    for (int i=0; i<4; i++){
        a = b % 256;
        printf("%c", a);
        b /= 256;
    }
    return 0;
} 