#include "pwd.h"

int mypwd() {
    char cwd[MAX_LINE_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
    return 0;
}

int main(int argc, char *argv[]) {
    mypwd(argc, argv);
    return 0;
}
