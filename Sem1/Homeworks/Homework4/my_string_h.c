/* my string.h */
#include <stdio.h>

char* mystrcpy(char* s, const char* ct){
	int i=-1;
	do {
		++i;
		s[i]=ct[i];
	} while (ct[i] != '\0');
	return s;
}

int mystrlen(const char* cs){
	int s=0;
	for (int i=0; cs[i]!='\0'; ++i)
		++s;
	return s;
}

char* mystrcat(char* s, const char* ct){
	int j=mystrlen(s);
	int i=-1;
	do {
		++i;
		s[j+i]=ct[i];
	} while (ct[i]!='\0');
	return s;
}

char mystrcmp(const char* cs, const char* ct){
	int i;
	for (i=0; cs[i]==ct[i]; ++i)
	{ }
	return (cs[i]-ct[i]);
}

char* mystrchr(const char* cs, char c){
	int i;
	for (i=0; cs[i]!=c && cs[i]!='\0'; ++i)
        {}
	if (cs[i]=='\0') return NULL;
	else return &cs[i];
}

char* mystrstr(const char* cs, const char* ct){
    int i;
	int flag=0;
        for (i=0; flag==0 && cs[i]!='\0'; ++i)
		    if (mystrcmp(cs+i, ct) == 0)
			    flag=1;
        if (flag==0) return NULL;
        else return &cs[i];
}

void* mymemcpy(void* s, const void* ct, size_t n){
	char* dst=s;
	const char* src=ct;
	for (int i=0; i<n; ++i)
		dst[i]=src[i];
	return s;
}

void* mymemset(void* s, char c, size_t n){
	char* dst=s;
	for (int i=0; i<n; ++i)
		dst[i]=c;
	return s;
}


int main(){
    
  	return 0;
}
