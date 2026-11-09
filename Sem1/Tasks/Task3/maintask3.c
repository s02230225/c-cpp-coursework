#include "module.h"

void err(state* st) {
        fprintf(stdout, "ERR !!!\n");
        fprintf(stderr, "ERR !!!\n");
        if (st->lst) {
                for (int i = 0; i < st->curlist; i++)
                        free(st->lst[i]);
                free(st->lst);
        }
        free(st->rb);
        exit(1);
}

void null_list(state* st) {
        st->sizelist = st->curlist = 0;
        st->lst = NULL;
}

void nullbuf(state* st) {
        st->sizebuf = st->curbuf = 0;
        st->buf = NULL;
}

void nullrb(state* st) {
        st->sizerb = st->currb = 0;
        st->rb = calloc(SIZE, sizeof(char));
}

int isspec(int c) {
        return (c == '|' || c == '&' || c == '>' || c == ';' || c == '<' || c == '(' || c == ')');
}

int symset(int c) {
        return (c != '\n' && c != ' ' && c != '\t' && (!isspec(c)) && c != EOF);
}

int iscorr(int c) {
        return (isalpha(c) || isdigit(c) || c == '$' || c == '_' || c == '/' || c == '.');
}

void printlist(state* st) {
        if (st == NULL || st->lst == NULL || st->sizelist <= 0) {
                return;
        }
        for (int i = 0; i < st->sizelist - 1; i++)
                printf("%s\n", st->lst[i]);
}

void clearlist(state* st) {
        st->sizelist = st->curlist = 0;
        if (st->lst) {
                for (int i = 0; st->lst[i] != NULL; i++)
                        free(st->lst[i]);
                free(st->lst);
                st->lst = NULL;
        }
}

int getsym(state* st) {
        int ret;
        if (st->currb >= st->sizerb) {
                if (fgets(st->rb, SIZE - 1, stdin) == NULL) {
                        return EOF;
                }
                st->sizerb = strlen(st->rb);
                st->currb = 0;
        }
        ret = st->rb[st->currb++];
        if ((!isspec(ret)) && (!iscorr(ret)) && ret != '\n' && ret != ' ' && ret != '\t' && ret != EOF) {
                fprintf(stderr, "Atata, bad input '%c'\n", ret);
                return ' ';
        }
        return ret;
}

void addsym(state* st) {
        if (st->curbuf > st->sizebuf - 1) {
                st->term = realloc(st->buf, st->sizebuf += SIZE);
                if (st->term) st->buf = st->term;
                else err(st);
        }
        st->buf[st->curbuf++] = st->c;
}

void addword(state* st) {
        if (st->curbuf > st->sizebuf - 1) {
                st->term = realloc(st->buf, st->sizebuf += 1);
                if (st->term) st->buf = st->term;
                else err(st);
        }
        st->buf[st->curbuf++] = '\0';
        st->term = realloc(st->buf, st->sizebuf += st->curbuf);
        if (st->term) st->buf = st->term;
        else err(st);
        if (st->curlist > st->sizelist - 1) {
                st->term = realloc(st->lst, (st->sizelist += SIZE) * sizeof(*st->lst));
                if (st->term) st->lst = st->term;
                else err(st);
        }
        st->lst[st->curlist++] = st->buf;
}

void termlist(state* st) {
        if (st->lst == NULL) return;
        if (st->curlist > st->sizelist - 1) {
                st->term = realloc(st->lst, (st->sizelist + 1) * sizeof(*st->lst));
                if (st->term) st->lst = st->term;
                else err(st);
        }
        st->lst[st->curlist] = NULL;
        st->term = realloc(st->lst, (st->sizelist = st->curlist + 1) * sizeof(*st->lst));
        if (st->term) st->lst = st->term;
        else err(st);
}

void bubble_sort(state* st) {
        if (st == NULL || st->lst == NULL || st->sizelist <= 0) {
                return;
        }
        for (int i = 0; i < st->sizelist - 1; i++) {
                for (int j = 0; j < st->sizelist - i - 2; j++) {
                        if (strcmp(st->lst[j], st->lst[j + 1]) > 0) {
                                char* temp = st->lst[j];
                                st->lst[j] = st->lst[j + 1];
                                st->lst[j + 1] = temp;
                        }
                }
        }
}
void reverse(state* st){
	if (st == NULL || st->lst==NULL || st->sizelist <= 0){
		return;
	}
	for (int i = 0; i < (st->sizelist-1)/2; i++){
		char* temp = st->lst[i];
		st->lst[i]=st->lst[st->sizelist-2-i];
		st->lst[st->sizelist-2-i]=temp;
	}
}

void outst(state* st){
        if (st->sizelist > 0){
                printf("%d WORDS IN STRING:\n", st->sizelist - 1);
                printf("!!! BEFORE SORT\n");
                printlist(st);
                bubble_sort(st);
                printf("!!! AFTER SORT\n");
                printlist(st);
		reverse(st);
		printf("!!! AFTER REVERSE\n");
		printlist(st);
		printf("\n");
        }
}

int main() {
        state st;
        nullrb(&st);
        nullbuf(&st);
        null_list(&st);
        st.c = getsym(&st); 
        while (1) {
                if (st.c == EOF) {
                        termlist(&st);
                        outst(&st);
                        clearlist(&st);
                        break;
                }
                else if (st.c == ' ' || st.c == '\t') {
                        st.c = getsym(&st);
                }
                else if (st.c == '\n') {
                        termlist(&st);
                        outst(&st);
                        st.c = getsym(&st);
                        clearlist(&st);
                }
                else {
                        nullbuf(&st);
                        addsym(&st);
                        if (st.c == ';' || st.c == '<' || st.c == '(' || st.c == ')') {
                                st.c = getsym(&st);
                        }
                        else if (st.c == '|') {
                                st.c = getsym(&st);
                                if (st.c == '|') {
                                        addsym(&st);
                                        st.c = getsym(&st);
                                }
                        }
                        else if (st.c == '&') {
                                st.c = getsym(&st);
                                if (st.c == '&') {
                                        addsym(&st);
                                        st.c = getsym(&st);
                                }
                        }
                        else if (st.c == '>') {
                                st.c = getsym(&st);
                                if (st.c == '>') {
                                        addsym(&st);
                                        st.c = getsym(&st);
                                }
                        }
                        else {
                                st.c = getsym(&st);
                                while (symset(st.c)) {
                                        addsym(&st);
                                        st.c = getsym(&st);
                                }
                        }
                        addword(&st);
                }
        }
        free(st.rb);
        printf("!!! PROGRAM ENDED CORRECTLY\n");
        return 0;
}
