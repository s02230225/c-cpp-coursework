/* mygrep */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getflag(char* str, int* pflag) {
    int i = 1;
    if (str[0] != '-') {
        *pflag = 0;
        return 0;
    }
    for (i = 1; str[i] != '\0'; ++i) {
        if (str[i] != 'v') {
            *pflag = 0;
            return 0;
        }
    }
    *pflag = 1;
    return 1;
}

int mygrep(int argc, char* argv[]) {
    if (argc > 4 || argc < 3) {
        fprintf(stderr,
                "Wrong number of args! Usage: [-v] <substring> <filename>\n");
        return 1;
    }
    FILE* file;
    errno = 0;
    int N = 256;
    int pos = 0;
    int flag = 0;
    char* str = calloc(N, sizeof(char));
    getflag(argv[1], &flag);
    char* substr;
    if (flag) {
        substr = argv[2];
        if ((file = fopen(argv[3], "r")) == NULL) {
            fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
            return 1;
        }
    }
    else {
        if (argc == 4) {
            fprintf(
                stderr,
                "Wrong number of args! Usage: [-v] <substring> <filename>\n");
            return 1;
        }
        substr = argv[1];
        if ((file = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
            return 1;
        }
    }
    while (fgets(str + pos, 256, file)) {
        // printf("str = %s\n", str);
        if (str == NULL)
            break;
        else if (!fseek(file, -1, SEEK_CUR) && '\n' != fgetc(file)){
            pos = N;
            N += 256;
        }
        else {
            if (flag) {
                if (strstr(str, substr) == NULL) {
                    printf("%s", str);
                }
            }
            else {
                if (strstr(str, substr)) {
                    printf("%s", str);
                }
            }
            free(str);
            N = 256;
            pos = 0;
            str = calloc(N, sizeof(char));
        }
    }
    free(str);
    fclose(file);
    return 0;
}

int main(int argc, char* argv[]) {
    mygrep(argc, argv);
}
