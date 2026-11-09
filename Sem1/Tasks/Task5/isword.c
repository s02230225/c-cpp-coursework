#include "isword.h"

int isfrom(char *s){
	return s != NULL && !strcmp(s, "<");
}

int isto(char *s){
	return s != NULL && !strcmp(s, ">");
}

int isappend(char *s){
	return s != NULL && !strcmp(s, ">>");
}

int isconv(char *s){
	return s != NULL && !strcmp(s, "|");
}

int isback(char *s){
	return s != NULL && !strcmp(s, "&");
}

int isfollow(char *s){
	return s != NULL && !strcmp(s, ";");
}

int isor(char *s){
	return s != NULL && !strcmp(s, "||");
}

int isand(char *s){
	return s != NULL && !strcmp(s, "&&");
}

int isopshell(char *s){
	return s != NULL && !strcmp(s, "(");
}

int iscloseshell(char *s){
	return s != NULL && !strcmp(s, ")");
}

int isexit(char *s){
	return s != NULL && !strcmp(s, "exit");
}

int iscd(char *s){
	return s != NULL && !strcmp(s, "cd");
}

int ispwd(char *s){
	return s != NULL && !strcmp(s, "pwd");
}

int issleep(char *s){
	return s != NULL && !strcmp(s, "sleep");
}

int isspecialword(char *s){
    if (s != NULL) return (!strcmp(s, "|") || !strcmp(s, "||") || !strcmp(s, "&") || !strcmp(s, "&&") || \
	!strcmp(s, "(") || !strcmp(s, ")") || !strcmp(s, ">") || !strcmp(s, ">>") || !strcmp(s, "<") || !strcmp(s, ";"));
    else return 1;
}