/* 3.22 */
#include <stdio.h>

int main(){
    int n, nc, sum=0;
    scanf("%d", &n);
    nc = n;
    while (nc>0){
        sum += (nc % 10);
        nc /= 10;
    } 
    if ((sum*sum*sum) == (n*n)) printf("yes"); else printf("no");
    return 0;
}