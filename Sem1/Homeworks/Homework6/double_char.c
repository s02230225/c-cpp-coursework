/* double char */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void double_bytes(const char *filename) {
    char byte;
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }
    off_t file_size = lseek(fd, 0, 2);
    if (file_size == -1) {
        printf("Error seeking to end of file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    for (off_t i = file_size - 1; i >= 0; i--) {
        if (lseek(fd, i, 0) == -1) {
            printf("Error seeking in file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (read(fd, &byte, 1) != 1) {
            printf("Error reading byte");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (lseek(fd, i+i, 0) == -1) {
            printf("Error seeking in file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (write(fd, &byte, 1) != 1) {
            printf("Error writing byte");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (write(fd, &byte, 1) != 1) {
            printf("Error writing byte");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>n", argv[0]);
        return EXIT_FAILURE;
    }
    double_bytes(argv[1]);
    return EXIT_SUCCESS;
}