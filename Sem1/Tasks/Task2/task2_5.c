/* task2.5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{
    max_len_word=1024
};

typedef struct nod {
    char *word;
    struct nod *next;
} nod;

nod* newnod(char* str, nod* prevnod){
    nod* ret=(nod*)calloc(1, sizeof(nod));
    ret->word=(char*)calloc(strlen(str), 1);
    strcpy(ret->word, str);
    ret->next=NULL;
    if (prevnod!=NULL) prevnod->next=ret;
    return ret;
}

void delnod(nod* thisnod, nod* prevnod){
    if (prevnod!=NULL) prevnod->next=thisnod->next;
    free(thisnod->word);
    free(thisnod);
}

void printfnod(nod* firstnod){
    nod* thisnod=firstnod;
    while(thisnod){
        printf("%s ", thisnod->word);
        thisnod=thisnod->next;
    }
    printf("\n");
}

nod* delcopynod(nod* firstnod, nod* lastnod){
    nod* thisnod;
    while (strcmp(firstnod->word, lastnod->word)==0 && firstnod->next!=NULL){
        thisnod=firstnod;
        firstnod=firstnod->next;
        delnod(thisnod, NULL);
    }
    if (firstnod==lastnod) return firstnod;
    thisnod=firstnod;
    while (thisnod->next!=lastnod && thisnod->next!=NULL){
        if (thisnod->next->next==lastnod && thisnod->next->word==lastnod->word){
            delnod(thisnod->next, NULL);
            thisnod->next=lastnod;
        }
        else if (strcmp(thisnod->next->word, lastnod->word)==0)
            delnod(thisnod->next, thisnod);
        thisnod=thisnod->next;
    }
    return firstnod;
}

void freeallnod(nod* firstnod){
    if (firstnod==NULL) return;
    while (firstnod->next)
        delnod(firstnod->next, firstnod);
    delnod(firstnod, NULL);
}

nod* maxlength(nod* firstnod){
	nod* ans=NULL;
	int maxlen=0;
	if (firstnod==NULL) return ans;
	else{
		for (; firstnod; firstnod=firstnod->next){
			if (strlen(firstnod->word)>maxlen){
				maxlen=strlen(firstnod->word);
				ans=firstnod;
			}
		}
		return ans;
	}
}

int main(){
    nod* firstnod, * lastnod;
    char str[max_len_word];
    if (scanf("%s", str)==-1) return 0;
    lastnod=firstnod=newnod(str, NULL);
    while (scanf("%s", str)!=-1)
        lastnod=newnod(str, lastnod);
    firstnod=delcopynod(firstnod, lastnod);
    lastnod=maxlength(firstnod);
    printf("\n%s with length %ld\n", lastnod->word, strlen(lastnod->word));
    printfnod(firstnod);
    freeallnod(firstnod);
    return 0;
}
