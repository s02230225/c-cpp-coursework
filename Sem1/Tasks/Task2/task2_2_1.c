/* task2_2_1 */
#include <stdio.h>

int main(){
    double x, ans, a;
    int in;
    in=scanf("%lg", &x);
    if (in!=1){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    in=scanf("%lg", &ans);
    if (in!=1){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    while ( (in=scanf("%lg", &a)) != -1 ){
        if (in!=1){
            fprintf(stdout, "bad input\n");
            return 5;
        }
        else{
            ans*=x;
            ans+=a;
        }
    }
    printf("%.10lg\n", ans);
    return 0;
} 