/* size_of_files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <путь_к_файлу1> <путь_к_файлу2> ...\n", argv[0]);
        return 1;
    }
    long total_size = 0;
    for (int i = 1; i < argc; i++) {
        struct stat file_stat;
        if (stat(argv[i], &file_stat) == -1) {
            perror("Ошибка при получении информации о файле");
        }
        else if (S_ISREG(file_stat.st_mode)) {
            total_size += file_stat.st_size;
        }
	else {
            fprintf(stderr, "Пропущен не-файл: %s\n", argv[i]);
        }
    }
    printf("Суммарный размер файлов: %ld байт\n", total_size);
    return 0;
}