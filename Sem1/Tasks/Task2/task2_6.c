/* task2.6 */
#include <stdio.h>
#include <stdlib.h>

#define Uint unsigned int

typedef struct nod {
    Uint key;
    struct nod *less, *more;
} nod;


nod* newnod(Uint val){
    nod* new=(nod*)calloc(1, sizeof(nod));
    new->key=val;
    new->less=NULL;
    new->more=NULL;
    return new;
}

nod* createnod(Uint val, nod* firstn){
    nod* thisn=firstn;
    if (firstn==NULL) return newnod(val);
    while (0==0){
        if (val==thisn->key) return firstn;
        else if (val<thisn->key){
            if (thisn->less==NULL){
                thisn->less=newnod(val);
                return firstn;
            }
            thisn=thisn->less;
        }
        else{
            if (thisn->more==NULL){
                thisn->more=newnod(val);
                return firstn;
            }
            thisn=thisn->more;
        }
    }
}

void changebranch(nod* thisn, nod* prevn){
    nod* root=NULL;
    if (thisn->key<prevn->key){
        if (thisn->less){
            prevn->less=thisn->less;
            root=thisn->less;
            while (root->more)
                root=root->more;
            root->more=thisn->more;
        }
        else prevn->less=thisn->more;
    }
    else{
        if (thisn->less){
            prevn->more=thisn->less;
            root=thisn->less;
            while (root->more)
                root=root->more;
            root->more=thisn->more;
        }
        else prevn->more=thisn->more;
    }
}

nod* deliten(Uint val, nod* firstn){
    nod* thisn=firstn;
    nod* prevn=firstn;
    if (firstn==NULL)
        return NULL;
    if (firstn->key==val){
        if (firstn->less==NULL){
            firstn=firstn->more;
            free(prevn);
            return firstn;
        }
        thisn=firstn->less;
        while (thisn->more)
            thisn=thisn->more;
        thisn->more=firstn->more;
        firstn=firstn->less;
        free(prevn);
        return firstn;
    }
    while (0==0){
        if (val==thisn->key){
            changebranch(thisn, prevn);
            free(thisn);
            return firstn;
        }
        else if (val<thisn->key){
            prevn=thisn;
            if (thisn->less)
                thisn=thisn->less;
            else return firstn;
        }
        else if (val>thisn->key){
            prevn=thisn;
            if (thisn->more)
                thisn=thisn->more;
            else return firstn;
        }
    }
}

int searchn(Uint val, nod* firstn){
    nod* thisn=firstn;
    if (firstn==NULL) return 0;
    while (0==0){
        if (val==thisn->key)
            return 1;
        else if (val<thisn->key){
            if (thisn->less)
                thisn=thisn->less;
            else return 0;
        }
        else if (val>thisn->key){
            if (thisn->more)
                thisn=thisn->more;
            else return 0;
        }
    }
}

void freealln(nod* thisnod){
    if (thisnod){
        freealln(thisnod->less);
        freealln(thisnod->more);
        free(thisnod);
        thisnod=NULL;
    }
}

int leafcount(nod* thisnod){
	int ans=0;
	if (thisnod==NULL) return 0;
	else if (thisnod->less==NULL && thisnod->more==NULL) return 1;
	else{
		if (thisnod->less) ans+=leafcount(thisnod->less);
		if (thisnod->more) ans+=leafcount(thisnod->more);
		return ans;
	}
}

/* debug print L-left, R-Right, U-Up*/
void printfn(nod* thisnod){
    if (thisnod){
        printf("<%u> ", thisnod->key);
        if (thisnod->less){
            printf("L "); 
            printfn(thisnod->less);
            printf("U ");
        }
        if (thisnod->more){
            printf("R ");
            printfn(thisnod->more);
            printf("U ");
        }
    }
}
/* --- */


int main(){
    nod *firstn=NULL;
    Uint val;
    char c;
    int in;
    while ((in=scanf(" %c%u", &c, &val))!=-1){
        if ((in!=2 || !(c=='+' || c=='-' || c=='?')) && !(in==1 && c=='\n')){
            fprintf(stderr, "bad input\n");
            return 5;
        }
        else if (c=='+'){
            firstn=createnod(val, firstn);
            /* for check graph */
            printfn(firstn);
            printf("\n");
	    printf("%d leaf(s) in tree\n", leafcount(firstn));
            /* --- */
        }
        else if (c=='-'){
            firstn=deliten(val, firstn);
            /* for check graph */
            printfn(firstn);
            printf("\n");
	    printf("%d leaf(s) in tree\n", leafcount(firstn));
            /* --- */
        }
        else if (c=='?'){
            if (searchn(val, firstn)) printf("%d yes\n", val);
            else printf("%d no\n", val);
	}
    }
    freealln(firstn);
    return 0;
}
