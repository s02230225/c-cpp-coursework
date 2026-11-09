/* head.c */
#include "head.h"

//////////////////////////////////
void printFileInfo(const char *path, const char *filename) {
    struct stat fileStat;
    char fullPath[MAX_LINE_LENGTH];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", path, filename);
    if (stat(fullPath, &fileStat) < 0) {
        perror("stat");
        return;
    }
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group *gr = getgrgid(fileStat.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);
    printf(" %ld", fileStat.st_size);
    printf(" %s\n", filename);
}

void listDirectory(const char *path, int longFormat, int showGroup) {
    struct dirent *directoryEntry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    while ((directoryEntry = readdir(dir)) != NULL) {
        if (directoryEntry->d_name[0] == '.')
            continue;
        if (longFormat)
            printFileInfo(path, directoryEntry->d_name);
        else
            printf("%s  ", directoryEntry->d_name);
    }
    printf("\n");
    closedir(dir);
}

///////////////////////////////////////////////
void listDirectoryRecursive(const char *path, int longFormat, int showGroup) {
    listDirectory(path, longFormat, showGroup);
    struct dirent *directoryEntry;
    DIR *dir = opendir(path);
    char subPath[MAX_LINE_LENGTH];
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    while ((directoryEntry = readdir(dir)) != NULL) {
        if (directoryEntry->d_type == DT_DIR && directoryEntry->d_name[0] != '.') {
            snprintf(subPath, sizeof(subPath), "%s/%s", path, directoryEntry->d_name);
            printf("\n%s:\n", subPath);
            listDirectoryRecursive(subPath, longFormat, showGroup);
        }
    }
    closedir(dir);
}

int myls(int argc, char *argv[]) {
    int longFormat = 0;
    int showGroup = 0;
    int recursive = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0)
            longFormat = 1;
        else if (strcmp(argv[i], "-g") == 0)
            showGroup = 1;
        else if (strcmp(argv[i], "-R") == 0)
            recursive = 1;
    }
    const char *path = ".";
    if (argc > 1 && argv[1][0] != '-')
        path = argv[1];
    if (recursive)
        listDirectoryRecursive(path, longFormat, showGroup);
    else
        listDirectory(path, longFormat, showGroup);
    return 0;
}

//////////////////////////////////////////////
void print_file(FILE *file, int *number_lines) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (*number_lines)
            printf("%6d\t%s", (*number_lines)++, line);
        else 
            printf("%s", line);
    }
}

int mycat(int argc, char *argv[]) {
    int number_lines = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] filenames...\n", argv[0]);
        return EXIT_FAILURE;
    }
	for (int i = 1; i < argc; i++){
    if (strcmp(argv[i], "-n") == 0)
        number_lines = 1;
}
    for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-n") != 0){
        	FILE *file = fopen(argv[i], "r");
        	if (file == NULL) {
        	    perror(argv[i]);
        	}
        	else {
        	    print_file(file, &number_lines);
        	    fclose(file);
        	}
	}
    }
    return EXIT_SUCCESS;
}

/////////////////////////////////////////////////////
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

////////////////////////////////////////////
void print_help_echo() {
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

int myecho(int argc, char *argv[]) {
    int print_newline = 1;
    int interpret = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help_echo();
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

///////////////////////////////////////////////////
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
    if (rename(old_file, new_file)!=0)
	perror("mv");
}

int mymv(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <old_file> <new_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
	if (strcmp(argv[1], argv[2]==0){
		printf("The same files\n");
		return 0;
	}
    const char *old_file = argv[1];
    const char *new_file = argv[2];
    move(old_file, new_file);
    return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////
int mypwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
    return 0;
}
