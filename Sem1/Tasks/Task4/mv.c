/* mv */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void copy_permissions(const char *src, const char *dest) {
    struct stat st;
    if (stat(src, &st) == -1) {
        perror("stat");
        return;
    }
    if (chmod(dest, st.st_mode) == -1)
        perror("chmod");
}

void move(const char *old_file, const char *new_file) {
    if (rename(old_file, new_file) == 0)
        copy_permissions(old_file, new_file);
    else
        perror("mv");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <old_file> <new_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *old_file = argv[1];
    const char *new_file = argv[2];
    move(old_file, new_file);
    return EXIT_SUCCESS;
}