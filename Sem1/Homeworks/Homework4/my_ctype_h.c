/* my ctype.h */
#include <stdio.h>

int myisupper(int c){
    return ('A'<=c && c<='Z');
}

int myislower(int c){
    return ('a'<=c && c<='z');
}

int myisalpha(int c){
    return (myisupper(c) || myislower(c));
}

int myisdigit(int c){
    return ('0'<=c && c<='9');
}

int myisalnum(int c){
    return (myisalpha(c) || myisdigit(c));
}

int myisxdigit(int c){       
	return (myisdigit(c) || ('A'<=c && c<='F'));
}

int myisspace(int c){       	                                                            
	return (c==' ' || c=='\t' || c=='\r' || c=='\n');
}

int myisgraph(int c){
	return(0x20<c && c<0x7F);
}	

int myisprint(int c){
    return (0x20<=c && c<0x7F);
}

int mytolower(int c){
	return (myisupper(c) ? c-'A'+'a' : c);
}

int mytoupper(int c){
    return (myisupper(c) ? c-'a'+'A' : c);
}


int main(){
    
	return 0;
}
