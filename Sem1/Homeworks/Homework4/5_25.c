/* 5.25 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b){
    return a>=b? a: b;
}

double bigmac(int n, double *m){
    double ans=-DBL_MAX;
    for (int i=0;i<=(int)(n+1);i++){
        ans=max(ans, m[i]+m[n-i-1]);
    }
    return ans;
}

int main(){
    double *p;
    int n;
    scanf("%d", &n);
    p=calloc(sizeof(double), n);
    for (int i=0;i<n;i++){
        scanf("%lf", &p[i]);
    }
    printf("%lf\n", bigmac(n, p));
    free(p);
    return 0;
}