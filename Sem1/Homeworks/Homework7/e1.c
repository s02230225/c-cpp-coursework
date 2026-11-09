/*  ejudge 1 */
#include <stdio.h>

int main(){
    int a, b, in;
    in=scanf("%d%d", &a, &b);
    if (in!=2){
        fprintf(stderr, "Err\n");
        return 1;
    }
    printf("%lld\n", (long long) a + b);
    return 0;
}