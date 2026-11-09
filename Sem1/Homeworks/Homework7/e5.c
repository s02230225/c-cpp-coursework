/*  ejudge 5 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc < 2) return 0;
    FILE **files = calloc(argc-1, sizeof(FILE *));
    int *current_values = calloc(argc-1, sizeof(int));
    int *eof_flags = calloc(argc-1, sizeof(int));
    int file_count = 0;
    for (int i = 1; i < argc; i++) {
        files[file_count] = fopen(argv[i], "r");
        if (!files[file_count])
            continue;
        if (fscanf(files[file_count], "%d", &current_values[file_count]) != 1)
            eof_flags[file_count] = 1;
        else
            eof_flags[file_count] = 0;
        file_count++;
    }
    while (1) {
        int min_value = __INT_MAX__;
        int min_index = -1;
        for (int i = 0; i < file_count; i++) {
            if (!eof_flags[i] && current_values[i] < min_value) {
                min_value = current_values[i];
                min_index = i;
            }
        }
        if (min_index == -1)
            break;
        printf("%d ", min_value);
        if (fscanf(files[min_index], "%d", &current_values[min_index]) != 1) {
            eof_flags[min_index] = 1;
        }
    }
    for (int i = 0; i < file_count; i++)
        fclose(files[i]);
    free(files);
    free(current_values);
    free(eof_flags);
    printf("\n");
    return 0;
}