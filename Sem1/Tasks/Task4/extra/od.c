/* myod */
#include <errno.h>
#include <stdio.h>
#include <string.h>

enum { N = 10 };

int prtspec(char c, int flag) {
    if (!flag) {
        switch (c) {
            case '\a': {
                printf("%c", '\\');
                printf("%c ", 'a');
                return 1;
            }
            case '\b': {
                printf("%c", '\\');
                printf("%c ", 'b');
                return 1;
            }
            case '\f': {
                printf("%c", '\\');
                printf("%c ", 'f');
                return 1;
            }
            case '\n': {
                printf("%c", '\\');
                printf("%c ", 'n');
                return 1;
            }
            case '\r': {
                printf("%c", '\\');
                printf("%c ", 'r');
                return 1;
            }
            case '\t': {
                printf("%c", '\\');
                printf("%c ", 't');
                return 1;
            }
            case '\v': {
                printf("%c", '\\');
                printf("%c ", 'v');
                return 1;
            }
        }
    }
    else
        printf("%x ", c);
    return 0;
}

int getflag(char* str, int* pflag) {
    int i = 1;
    if (str[0] != '-') {
        *pflag = 0;
        return 0;
    }
    for (i = 1; str[i] != '\0'; ++i) {
        if (str[i] != 'b') {
            *pflag = 0;
            return 0;
        }
    }
    *pflag = 1;
    return 1;
}

int myod(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Wrong number of args! Usage: [-b] <filename>\n");
        return 1;
    }
    int flag = 0;
    errno = 0;
    getflag(argv[1], &flag);
    FILE* f = NULL;
    if (flag == 0) {
        if (argc != 2) {
            fprintf(stderr, "Wrong number of args! Usage: [-b] <filename>\n");
            return 1;
        }
        f = fopen(argv[1], "r");
    }
    else {
        if (argc != 3) {
            fprintf(stderr, "Wrong number of args! Usage: [-b] <filename>\n");
            return 1;
        }
        f = fopen(argv[2], "r");
    }
    if (f == NULL) {
        fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
        return 1;
    }
    char c = '\0';
    int i = 0;
    for (int cnt = 1; (c = fgetc(f)) != EOF; ++cnt) {
        i = (cnt - 1) % 10;
        if (i == 0) {
            printf("\n%06d ", cnt);
        }
        if (!prtspec(c, flag)) {
            if (flag)
                printf("%x ", c);
            else
                printf("%c ", c);
        }
    }
    printf("\n");
    fclose(f);
    return 0;
}

int main(int argc, char* argv[]) {
    myod(argc, argv);
}
