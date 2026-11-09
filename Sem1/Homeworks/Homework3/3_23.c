/* 3.23 */
#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    while(n%3==0){
       n/=3;
    }
    (n==1) ? printf("yes"): printf("no");
} 