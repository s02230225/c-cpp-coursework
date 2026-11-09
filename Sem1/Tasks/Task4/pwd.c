/* pwd */
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void print_working_directory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

int main() {
    print_working_directory();
    return 0;
}