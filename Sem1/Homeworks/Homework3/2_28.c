/* 2.28 */
#include <stdio.h>
#include <math.h>

int p2(int n){
    if (n==0) return 1;
    else if (n>0) return 2<<n;
    else return (int) pow(2, n);
}

int main(){
    int x, n, right_part, left_part;
    scanf("%d %d", &x, &n);
    right_part = x % p2(n);
    left_part = x / p2(n);
    x = left_part * p2(32-n);
    x += right_part;
    printf("%d", x);
    return 0;
}