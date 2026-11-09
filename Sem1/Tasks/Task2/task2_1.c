/* task2_1 */
#include <stdio.h>

/* modulus of difference */
double md(double x, double y){
    return x>=y ? x-y : y-x;
}

int main(){
    double ep, x, x0, x1;
    int in;
    in=scanf("%lg", &ep);
    if (in!=1){
        fprintf(stderr, "bad input\n");
        return 5;
    }
    while ( (in=scanf("%lg", &x)) != -1 ){
        if (in!=1){
            fprintf(stdout, "bad input\n");
            return 5;
        }
        else if (x<0){
            fprintf(stderr, "the root of the negative\n");
            return 95;
        }
        else if (x==0){
            printf("%.10lg\n", 0.0);
        }
        else {
            x0=1;
            x1=0.5*(x0+x/x0);
            while (md(x0,x1)>=ep){
                x0=x1;
                x1=0.5*(x0+x/x0);
            }
            printf("%.10lg\n", x1);
        }
    }
    return 0;
} 