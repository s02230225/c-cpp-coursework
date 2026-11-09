/* task1_4 */
#include <stdio.h>


void outp(char a, char b){
    if (a<=b)
        for (int i=a; i<=b; i++)
            printf("'%c' - %d\n", i, (int) i);
    else
        for (int i=a; a>=b; i--)
            printf("'%c' - %d\n", i, (int) i);
    printf("\n");
}

int main(){
    printf("'%c' - %d\n\n", ' ', (int) ' ');
    outp('0', '9');
    outp('A', 'Z');
    outp('a', 'z');
    printf("%d\n", (int)('Z'-'0'));
    return 0;
}
