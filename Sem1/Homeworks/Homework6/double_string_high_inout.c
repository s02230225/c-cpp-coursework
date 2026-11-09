/* double_string_high_inout */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void double_bytes(const char *filename) {
    char byte1;
    FILE *fd = fopen(filename, "r+");
    int x;
    fseek(fd, 0, 2);
    long file_size = ftell(fd);
    fseek(fd, 0, 0);
    byte1='\n';
    fwrite(&byte1, 1, 1, fd);
    file_size+=1;
    x=file_size+file_size-1;
    for (long i = file_size - 1; i >= 0; i--) {
        fseek(fd, i, 0);
        fread(&byte1, 1, 1, fd);
        if (byte1=='\n'){
            byte1='\n';
            fseek(fd, x--, 0);
            fwrite(&byte1, 1, 1, fd);
            for (off_t j=i-1; j>=0; j--){
                fseek(fd, j, 0);
                fread(&byte1, 1, 1, fd);
                if (byte1=='\n') break;
                fseek(fd, x--, 0);
                fwrite(&byte1, 1, 1, fd);
            }
            byte1='\n';
            fseek(fd, x--, 0);
            fwrite(&byte1, 1, 1, fd);
            for (off_t j=i-1; j>=0; j--){
                fseek(fd, j, 0);
                fread(&byte1, 1, 1, fd);
                if (byte1=='\n') break;
                fseek(fd, x--, 0);
                fwrite(&byte1, 1, 1, fd);
            }
            
        }
    }
    fclose(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>n", argv[0]);
        return EXIT_FAILURE;
    }
    double_bytes(argv[1]);
    return EXIT_SUCCESS;
}