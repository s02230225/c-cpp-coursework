#include "wc.h"

void count_file(const char *filename, long *lines, long *words, long *chars) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }
    int c, in_word = 0;
    *lines = *words = *chars = 0;
    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') {
            (*lines)++;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        }
        else {
            if (!in_word) {
                (*words)++;
                in_word = 1;
            }
        }
    }
    fclose(file);
}

int mywc(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Use: %s file1 [file2 ...]\n", argv[0]);
        return 1;
    }
    long total_lines = 0, total_words = 0, total_chars = 0;
    for (int i = 1; i < argc; i++) {
        long lines = 0, words = 0, chars = 0;
        count_file(argv[i], &lines, &words, &chars);
        if (!(lines == 0 && words == 0 && chars == 0)) {
            printf("%s %ld %ld %ld\n", argv[i], lines, words, chars);
            total_lines += lines;
            total_words += words;
            total_chars += chars;
        }
    }
    printf("Итого: %ld %ld %ld\n", total_lines, total_words, total_chars);
    return 0;
}

int main(int argc, char *argv[]) {
    mywc(argc, argv);
    return 0;
}
