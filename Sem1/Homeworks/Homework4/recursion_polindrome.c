/* recursion palindrome */
#include <stdio.h>
#include <string.h>

int palindrom(char *s){
    int n, ans;
    char k;
    for (n=0; s[n]!='\0'; ++n)
	    {}
    if (n==1) return 1;
    else if (n==2 && s[0]==s[1]) return 1;
    else if (s[0]==s[n-1]){
        k=s[n-1];
        s[n-1]='\0';
        ans=palindrom(s+1);
        s[n-1]=k;
        return ans;
    }
    else return 0;
}

int main(int argc, char **argv){
    printf ("%salindrome\n", (palindrom(argv[1])) ? "P" : "Not a p");
    return 0;
}
