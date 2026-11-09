/* ls */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

enum { max_size=1024 };

void printFileInfo(const char *path, const char *filename) {
    struct stat fileStat;
    char fullPath[max_size];
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


void listDirectoryRecursive(const char *path, int longFormat, int showGroup) {
    listDirectory(path, longFormat, showGroup);
    struct dirent *directoryEntry;
    DIR *dir = opendir(path);
    char subPath[max_size];
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

int main(int argc, char *argv[]) {
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
