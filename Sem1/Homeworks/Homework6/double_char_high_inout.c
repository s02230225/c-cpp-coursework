/* double_char_high_inout */
#include <stdio.h>
#include <stdlib.h>

void err(FILE *file){
    fprintf(stderr, "Err!!!\n");
    fclose(file);
    exit(1);
}

void duplicate_bytes_high(const char *filename) {
	FILE *file = fopen(filename, "r+");
    long file_size;
    unsigned int byte;
	if (file == NULL)
        fprintf(stderr, "Cannot open file\n");
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	if (file_size == -1) err(file);
    for (long i = file_size - 1; i >= 0; --i) {
        fseek(file, i, SEEK_SET);
        if (fread(&byte, 1, 1, file) != 1) err(file);
	    fseek(file, i * 2, SEEK_SET);
	    if (fwrite(&byte, 1, 1, file) != 1 || fwrite(&byte, 1, 1, file) != 1) err(file);
    }
	fclose(file);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Wrong input! Usage: <filename>\n");
        	return 1;
	}
	duplicate_bytes_high(argv[1]);
	return 0;
}

