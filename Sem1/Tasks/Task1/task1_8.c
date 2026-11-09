/* task1_8 */
#include <stdio.h>


int main(){
    int a, b, c;
    a=13; b=3;
    printf("divisible / divisor = quotient (remainder)\n");
    printf("%d / %d = %d (%d)\n", a,b,a/b,a%b);
    a=-13; b=3;
    printf("%d / %d = %d (%d)\n", a,b,a/b,a%b);
    a=13; b=-3;
    printf("%d / %d = %d (%d)\n", a,b,a/b,a%b);
    a=-13; b=-3;
    printf("%d / %d = %d (%d)\n", a,b,a/b,a%b);

    printf("input a b: ");
    c=scanf("%d %d", &a, &b);
    printf("%d\n", c);
    if (c!=2)
        printf("Next time, enter exactly two integer (signed) numbers.\n");
    else if (b==0)
        printf("Hey, you're trying to divide by zero!\n");
    else
        printf("%d / %d = %d (%d)\n", a, b, a/b, a%b);
    return 0;
}
