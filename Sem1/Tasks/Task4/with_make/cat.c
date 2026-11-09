#include "cat.h"

void print_file(FILE *file, int *number_lines, int *flag) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if ((*number_lines) && (*flag)){
            printf("%6d\t%s", (*number_lines)++, line);
            (*flag) = 1;
        }
        else if ((*number_lines) && !(*flag)){
            printf("%s", line);
            (*flag) = 1;
        }
        else 
            printf("%s", line);
    }
}

int mycat(int argc, char *argv[]) {
    int number_lines = 0;
    int flag = 1;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] filenames...\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-n") == 0)
            number_lines = 1;
    }
    for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-n") != 0) {
        	FILE *file = fopen(argv[i], "r");
        	if (file == NULL) {
        	    perror(argv[i]);
        	}
        	else {
        	    print_file(file, &number_lines, &flag);
                flag = 0;
        	    fclose(file);
        	}
	}
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    mycat(argc, argv);
    return 0;
}
