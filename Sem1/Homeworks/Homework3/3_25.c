/* 3.25 */
#include <stdio.h>

int main(){
    float a, sum=0;
    int n=1;
    scanf("%e", &a);
    while (sum<=a){
        sum += 1.0/(double)n;
        n++;
    }
    printf("%d", n-1);
    return 0;
} 