/* cat */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_LINE_LENGTH=1024 };

void print_file(FILE *file, int *number_lines) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (*number_lines)
            printf("%6d\t%s", (*number_lines)++, line);
        else 
            printf("%s", line);
    }
}

int main(int argc, char *argv[]) {
    int number_lines = 0, start_index = 1;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] filenames...\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "-n") == 0) {
        number_lines = 1;
        start_index++;
    }
    for (int i = start_index; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror(argv[i]);
        }
        else {
            print_file(file, &number_lines);
            fclose(file);
        }
    }
    return EXIT_SUCCESS;
}
