/* 6_46 */
#include <stdio.h>

typedef struct nod {
    int val;
    struct nod *left, *right;
} nod;

//////////////a
int countn(nod* tn, int k){
    if (tn) return (tn->val==k)+countn(tn->left, k)+countn(tn->right, k);
    else return 0;
}

//////////////b
int sumn(nod* tn, int k){
    if (tn) return (tn->val)+countn(tn->left, k)+countn(tn->right, k);
    else return 0;
}

/////////////c
int elinn (nod* tn, int k){
    if (countn(tn, k)) return 1;
    else return 0;
}

/////////////d
void printn(nod* tn){
    if (tn){
        if (tn->left || tn->right){
            printf("%d ", tn->val);
            if (tn->left) printn(tn->left);
            if (tn->right) printn(tn->right);
        }
    }
}

////////////e
int equaln(nod* n1, nod* n2){
    int v=0,l=0,r=0;
    if (n1 && n2){
        if (n1->val==n2->val) v=1;
        if(n1->left && n2->left) l=equaln(n1->left, n2->left);
        if(n1->right && n2->right) l=equaln(n1->right, n2->right);
        return v*l*r;
    }
    else if (n1==NULL && n2==NULL) return 1;
    else return 0;
}

int main(){
    
} 