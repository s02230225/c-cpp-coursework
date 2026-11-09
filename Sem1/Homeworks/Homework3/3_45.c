/* 3.45 */
#include <stdio.h>
#include <math.h>

int perfect_number(int n){
    int k=(int) floor(pow(n, 0.5))+1;
    int s=0;
    for (int i=2; i<k; i++){
        if ( ((n%i)==0) && ((int)pow(i, 2)!=n) ) s += (i+(int)(n/i));
        if ((n%i)==0) s += i;
    }
    if (s==n) return 1;
    else return 0;
}
int main(){
    int n, rez;
    scanf("%d", &n);
    for (int i=1; i<n; i++) {
        rez+=perfect_number(i);
    }
    printf("answer: %d\n", rez);
    return 0;
}
