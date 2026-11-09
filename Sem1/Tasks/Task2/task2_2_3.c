/* task2_2_3 */
#include <stdio.h>

int main(){
    double x, ans1, a, ans2, ans3;
    int n, in;
    in=scanf("%d", &n);
    if (in!=1 || n<0){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    in=scanf("%lg", &x);
    if (in!=1){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    in=scanf("%lg", &ans1);
    if (in!=1){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    ans2=0;
    ans3=ans1/n*x;
    n--;
    while ( (in=scanf("%lg", &a)) != -1 ){
        if (in!=1){
            fprintf(stdout, "bad input\n");
            return 5;
        }
        else{
            ans2=ans1+x*ans2;
            ans1*=x;
            ans1+=a;
            ans3+=a/n;
            ans3*=x;
            n--;   
        }
    }
    printf("%.10lg\n", ans1);
    printf("%.10lg\n", ans2);
    printf("%.10lg\n", ans3);
    return 0;
} 