/* number_8 ? */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void process_file(const char *filename, int N) {
    if (N < 1) {
        return; // Если N < 1, ничего не делаем
    }

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Определяем размер файла
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size <= 0 || file_size % sizeof(double) != 0) {
        close(fd);
        return; // Если файл пуст или не кратен размеру double, ничего не делаем
    }

    int num_elements = file_size / sizeof(double);
    if (num_elements <= 1) {
        close(fd);
        return; // Если в файле одно или ноль чисел, ничего не делаем
    }

    // Ограничиваем количество обрабатываемых элементов до N
    if (N > num_elements) {
        N = num_elements;
    }

    lseek(fd, 0, SEEK_SET); // Возвращаемся в начало файла

    double prev_value, current_value;
    read(fd, &prev_value, sizeof(double)); // Читаем первое значение

    for (int i = 1; i < N; i++) {
        read(fd, &current_value, sizeof(double)); // Читаем текущее значение
        current_value -= prev_value; // Применяем формулу
        lseek(fd, -sizeof(double), SEEK_CUR); // Возвращаемся на одно значение назад
        write(fd, &current_value, sizeof(double)); // Записываем измененное значение
        prev_value = current_value; // Обновляем предыдущее значение
    }

    close(fd); // Закрываем файл
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <N>n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int N = atoi(argv[2]);

    process_file(filename, N);

    return EXIT_SUCCESS;
}