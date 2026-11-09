/* 3.49(h) */
#include <stdio.h>

int isd(char c){
    if (('0'<=c) && (c<='9')) return 1;
    else return 0;
}

int main(){
    char c1, c2;
    int flag;
    c2=getchar();
    if (c2=='0') flag=0;
    else flag=1;
    do {
        c1=c2;
        c2=getchar();
        if (c1!='0'){
            printf("%c", c1);
            if (isd(c1)) flag=1;
            else flag=0;
        }
        else if ((flag==1) || !isd(c2)){
            printf("%c", c1);
        }
    } while(c2!='.');
    printf("%c\n", c2);
} 