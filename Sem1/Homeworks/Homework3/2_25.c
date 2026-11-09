/* 2.25 */
#include <stdio.h>

int main(){
    int i; char a;
    unsigned int ans = 0;
    for (i=0; i<3; i++){
        scanf("%c", &a);
        ans += a;
        ans <<= 8;
    }
    scanf("%c", &a);
    ans += a;
    printf("%u", ans);
    return 0;
} 