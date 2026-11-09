/* cmp */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int mycmp(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Wrong args number! Usage: <filename1> <filename2>\n");
        return 1;
    }
    FILE* file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        fprintf(stderr, "Error in opening first file: %s\n", strerror(errno));
        return 1;
    }
    FILE* file2 = fopen(argv[2], "r");
    if (file2 == NULL) {
        fprintf(stderr, "Error in opening second file: %s\n", strerror(errno));
        fclose(file1);
        return 1;
    }
    int flagread = 1 != 2;
    int curline = 1, curbyte = 0, n1, n2;
    char c1 = '\0', c2 = '\0';
    while (flagread) {
        curbyte += 1;
        n1 = fread(&c1, 1, 1, file1);
        n2 = fread(&c2, 1, 1, file2);
        if (n1 != n2) {
            if (n1 == 0) {
                if (c1 == '\n') curline--;
                printf("Met EOF in %s after byte %d, line %d\n", argv[1],
                       curbyte - 1, curline);
            }
            else if (n2 == 0) {
                if (c2 == '\n') curline--;
                printf("Met EOF in %s after byte %d, line %d\n", argv[2],
                       curbyte - 1, curline);
            }
            flagread = 0;
        }
        else if (n1 == 0) {
            flagread = 0;
        }
        else {
            if (c1 == c2) {
                if (c1 == '\n') curline += 1;
            }
            else {
                printf("%s %s have difference in byte %d, line %d\n", argv[1],
                       argv[2], curbyte, curline);
                flagread = 0;
            }
        }
    }
    fclose(file1);
    fclose(file2);
    return 0;
}

int main(int argc, char** argv){
    mycmp(argc, argv);
}