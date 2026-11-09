/* str reverse */
#include <stdio.h>

void reverse(char *str){
	int n;
    char k;
	for (n = 0; str[n] != '\0'; ++n)
	    {}
	for (int i = 0; i < (n/2); ++i){
        k=str[i];
        str[i]=str[n-i-1];
        str[n-i-1]=k;
    }
}

int main(){
	char s;
	scanf("%s", &s);
    reverse(&s);
	printf("%s\n", &s);
    return 0;
}

