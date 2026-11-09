/* double string */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void double_bytes(const char *filename) {
    char byte1;
    int fd = open(filename, O_RDWR);
    int x;
    off_t file_size = lseek(fd, 0, 2);
    byte1='\n';
    write(fd, &byte1, 1);
    file_size+=1;
    x=file_size+file_size-1;
    for (off_t i = file_size - 1; i >= 0; i--) {
        lseek(fd, i, 0);
        read(fd, &byte1, 1);
        if (byte1=='\n'){
            byte1='\n';
            lseek(fd, x--, 0);
            write(fd, &byte1, 1);
            for (off_t j=i-1; j>=0; j--){
                lseek(fd, j, 0);
                read(fd, &byte1, 1);
                if (byte1=='\n') break;
                lseek(fd, x--, 0);
                write(fd, &byte1, 1);
            }
            byte1='\n';
            lseek(fd, x--, 0);
            write(fd, &byte1, 1);
            for (off_t j=i-1; j>=0; j--){
                lseek(fd, j, 0);
                read(fd, &byte1, 1);
                if (byte1=='\n') break;
                lseek(fd, x--, 0);
                write(fd, &byte1, 1);
            }
            
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