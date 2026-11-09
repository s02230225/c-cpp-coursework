/* task2_3 */
#include <stdio.h>
#include <time.h>

int fib_iter(int n){
    int f1, f2, f;
    if (n<2) return n;
    f1=0; f2=1;
    for (;n>=2;n--){
        f=f1+f2;
        f1=f2;
        f2=f;
    }
    return f2;
}

int fib_rec(int n){
    if (n<2) return n;
    else return fib_rec(n-1)+fib_rec(n-2);
}

int main(){
    int n, in, ans;
    long start, stop;
    in=scanf("%d", &n);
    if (in!=1 || n<0){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    start=clock();
    ans=fib_iter(n);
    stop=clock();
    printf("the time of the iterative function: %ld msec\n", (stop-start));
    printf("with the result: %d\n", ans);
    start=clock();
    ans=fib_rec(n);
    stop=clock();
    printf("the time of the recurrent function: %ld msec\n", (stop-start));
    printf("with the result: %d\n", ans);
    return 0;
} 