#ifndef ISWORD_H
#define ISWORD_H

#include <string.h>

int isfrom(char *s);
int isto(char *s);
int isappend(char *s);
int isconv(char *s);
int isback(char *s);
int isfollow(char *s);
int isor(char *s);
int isand(char *s);
int isopshell(char *s);
int iscloseshell(char *s);
int isexit(char *s);
int iscd(char *s);
int ispwd(char *s);
int issleep(char *s);
int isspecialword(char *s);

#endif //ISWORD_H