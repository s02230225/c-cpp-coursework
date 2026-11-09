/* 3.18 */
#include <stdio.h>

int main(){
    int a, b, c, exactly, atleast;
    exactly=0;
    atleast=0;
    for (int i=111; i<=999; i++){
        a = i%10;
        b = (i/10)%10;
        c = i/100; 
        if ((a==b) || (a==c) || (b==c)) atleast++;
        if ((a==b && b!=c) || (a==c && c!=b) || (b==c && c!=a)) exactly++;
    }
    printf("exactly: %d, atleast: %d\n", exactly, atleast);
    return 0;
} 