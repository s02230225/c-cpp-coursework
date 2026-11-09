/* echo */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_help() {
    printf("Usage: echo [OPTION]... [STRING]...\n");
    printf("Display the STRING(s) to standard output.\n");
    printf("  -n            do not output the trailing newline\n");
    printf("  -e            enable interpretation of backslash escapes\n");
    printf("  -E            disable interpretation of backslash escapes\n");
    printf("  --help        display this help message and exit\\n");
}

void interpret_and_print(const char *str, int interpret) {
    if (!interpret) {
        printf("%s", str);
        return;
    }
    while (*str) {
        if (*str == '\\') {
            str++;
            if (*str=='n')
                putchar('\n');
            else if (*str=='t')
                putchar('\t');
            else if (*str=='r')
                putchar('\r');
            else if (*str=='b')
                putchar('\b');
            else if (*str=='f')
                putchar('\f');
            else if (*str=='a')
                putchar('\a');
            else if (*str=='\\')
                putchar('\\');
            else if (*str=='c') ;
            else if (isdigit(*str)) {
                int value = 0;
                while (isdigit(*str)) {
                    value = value * 8 + (*str - '0');
                    str++;
                }
                putchar(value);
                str--;
            }
            else
                putchar(*str);
        }
        else
            putchar(*str);
        str++;
    }
}

int main(int argc, char *argv[]) {
    int print_newline = 1;
    int interpret = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
        else if (strcmp(argv[i], "-n") == 0)
            print_newline = 0;
        else if (strcmp(argv[i], "-e") == 0)
            interpret = 1;
        else if (strcmp(argv[i], "-E") == 0)
            interpret = 0;
        else {
            interpret_and_print(argv[i], interpret);
            if (i < argc - 1)
                putchar(' ');
        }
    }
    if (print_newline)
        putchar('\n');
    return 0;
}