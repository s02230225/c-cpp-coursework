/* tail */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { N = 10 };

int getflag(char* str, int* pval, int* pflag) {
    int i = 1;
    *pval = N;
    if (str[0] == '-' || str[0] == '+') {
        *pflag = str[0];
        int s = 0;
        for (i = 1; str[i] != '\0'; ++i) {
            if (str[i] > '9' || str[i] < '0') {
                *pflag = 0;
                return 0;
            }
            s = s * 10 + (str[i] - '0');
        }
        *pval = s;
        return 1;
    } else {
        *pflag = 0;
        return 0;
    }
}

int mytail(int argc, char* argv[]){
    if (argc < 2 || argc > 3) {
        fprintf(stderr,
                "Wrong number of args! Usage: [-<int> / +<int>] <filename>\n");
        return 1;
    }
    int flag = 0;
    int val = 10;
    errno = 0;
    getflag(argv[1], &val, &flag);
    FILE* f = NULL;
    if (flag == 0) {
        if (argc != 2) {
            fprintf(
                stderr,
                "Wrong number of args! Usage: [-<int> / +<int>] <filename>\n");
            return 1;
        }
        f = fopen(argv[1], "r");
    }
    else {
        if (argc != 3) {
            fprintf(
                stderr,
                "Wrong number of args! Usage: [-<int> / +<int>] <filename>\n");
            return 1;
        }
        f = fopen(argv[2], "r");
    }
    if (f == NULL) {
        fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
        return 1;
    }
    int strcnt = 0;
    char c;
    int pos = 0, i;
    for (i = 0; (c = fgetc(f)) != EOF; ++i) {
        if (c == '\n') {
            pos = i;
            ++strcnt;
        }
    }
    if (pos != i)
        ++strcnt;
    fseek(f, 0, SEEK_SET);
    i = 0;
    pos = 0;
    char *check= NULL;
    char* str = calloc(256, sizeof(char));
    if (flag == '+') {
        while (fgets(str + pos, 256, f)) {
            if (str == NULL)
                break;
            else if (fseek(f, -1, SEEK_CUR) == 0 && fgetc(f) != '\n'){
                pos += 256;
                check = realloc(str, pos + 256);
            }
            else {
                ++i;
                if (i >= val) printf("%s", str);
                free(str);
                pos = 0;
                str = calloc(256, sizeof(char));
            }
        }
    }
    else {
        while (fgets(str + pos, 256, f)) {
            if (str == NULL)
                break;
            else if (ftell(f) % 256 == 0) 
            {
                pos += 256;
                check = realloc(str, pos + 256);
            }
            else {
                ++i;
                if (i >= (strcnt - val)) printf("%s", str);

                free(str);
                pos = 0;
                str = calloc(256, sizeof(char));
            }
        }
    }
    free(str);
    fclose(f);
    return 0;
}

int main(int argc, char* argv[]){
    mytail(argc, argv);
}
