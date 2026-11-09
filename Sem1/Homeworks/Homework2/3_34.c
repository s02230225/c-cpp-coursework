/* 3.34 */
#include <stdio.h>

int main(){
    int n, fs, fn_1=1, fn=1;
    scanf("%d", &n);
    if (n<0) printf("Error input");
    else if ((n==0) || (n==1)) printf("1");
    else {
        for (int i=3; i<=n; ++i){
            fs=fn;
            fn+=fn_1;
            fn_1=fs;
            }
        printf("%d", fn);
    }
}