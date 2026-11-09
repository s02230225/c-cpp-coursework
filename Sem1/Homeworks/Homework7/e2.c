/*  ejudge 2 */
#include <stdio.h>

int main(){
    long long ans=0;
    char c;
    while (scanf("%c", &c)==1) {
        if ('0'<=c && c<='9') ans+=(long long)(c-'0');
        else if ('a'<=c && c<='f') ans+=(long long)(c-'a'+10);
        else if ('A'<=c && c<='F') ans+=(long long)(c-'A'+10);
    }
    printf("%lld\n", ans);
    return 0;
}