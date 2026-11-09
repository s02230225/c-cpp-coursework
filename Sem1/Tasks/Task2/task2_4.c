/* task2_4 */
#include <stdio.h>

enum{
    max_len_double=128
};

double powm(int n){
    double ans=1;
    if (n>0)
        for (;n!=0;n--)
            ans*=10;
    else
        for (;n!=0;n++)
            ans*=0.1;
    return ans;
}

double str2double(char str[]){
    int sign_man=1, sign_ext=1, man=0, ext1=0, ext2=0, flag=0, a;
    char c;
    for (int i=0; i<max_len_double; i++){
        c=str[i];
        if (c=='-'){
            if (flag==0)
                sign_man=-1;
            else
                sign_ext=-1;
        }
        else if (c=='.'){
            flag=1;
        }
        else if (c=='e' || c=='E'){
            flag=2;
        }
        else if ('0'<=c && c<='9'){
            a=(int)(c-'0');
            if (flag==0){
                man*=10;
                man+=a;
            }
            else if (flag==1){
                man*=10;
                man+=a;
                ext1--;
            }
            else{
                ext2*=10;
                ext2+=a;
            }
        }
        else if (c=='\0'){
            break;
        }
        /* no check for incorrect input */
    }
    return (double)sign_man*man*powm(ext1+sign_ext*(ext2));
}

int main(){
    char str[max_len_double];
    while(scanf("%s", str)!=-1){
        printf("%.10g\n",str2double(str));
    }
    return 0;
}