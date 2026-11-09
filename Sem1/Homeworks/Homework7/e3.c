/*  ejudge 3 */
#include <stdio.h>
#include <limits.h>
int main(){
    int a, b, in;
    unsigned n;
    in = scanf("%d %d %u", &a, &b, &n);
    if ((in != 3) || (n == 0) || (a >= b)){
        fprintf(stderr, "Err\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
        printf(" ");
    for (int i = a; i < b; i++)
        printf(" %*d", n, i);
    printf("\n");
    for (int i = a; i < b; i++) {
        printf("%*d", n,  i);
        for (int j = a; j < b; j++)
            printf(" %*lld", n, (long long)i * (long long)j);
        printf("\n");
    }
    return 0;
}
