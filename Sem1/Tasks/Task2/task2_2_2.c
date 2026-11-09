/* task2_2_2 */
#include <stdio.h>

int main(){
    double x, ans1, a, ans2;
    int in;
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
    while ( (in=scanf("%lg", &a)) != -1 ){
        if (in!=1){
            fprintf(stdout, "bad input\n");
            return 5;
        }
        else{
            ans2=ans1+x*ans2;
            ans1*=x;
            ans1+=a;
        }
    }
    printf("%.10lg\n", ans1);
    printf("%.10lg\n", ans2);
    return 0;
} 