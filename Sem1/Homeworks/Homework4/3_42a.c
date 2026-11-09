/* 3.42a */
#include <stdio.h>
#include <math.h>

int main(){
    double x, s, ans;
    int n;
    scanf("%lf", &x);
    scanf("%d", &n);
    s=1;
    for (int i=0; i<n; i++, s*=sin(x)){
        ans+=s;
    }
    printf("%lf", ans);
    return 0;
}