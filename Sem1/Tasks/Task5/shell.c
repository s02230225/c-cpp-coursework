#include "isword.h"
#include "list.h"
#include "tree.h"
#include "shlfunc.h"

jmp_buf begin; // Используется для возврата в начало программы
jmp_buf sexit; // Используется для выхода из программы
extern int last_pid;

// Обработчик сигнала SIGINT (обычно вызывается при нажатии Ctrl+C)
void handle_signal(int signal) {
    if (signal == SIGINT) {
        longjmp(begin, 1); // Возвращаемся в точку, где был вызван setjmp
    }
}

int main(int argc, char** argv) {
    list ls = NULL;
    tree t1 = NULL;
    list qur = NULL;
    int endofshellint, stat; // Переменные для состояния и статуса завершения
    int ansrec = 0; // Переменная для хранения глубины рекурсии pipe
    // Установка обработчика для сигнала SIGINT
    signal(SIGINT, handle_signal); 
    if (argc > 2) {
        fprintf(stderr, "TOO MANY ARGUMENTS\n");
        return EXIT_FAILURE;
    }
    // Если передан один аргумент, открываем файл для чтения
    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("FILE OPEN ERROR");
            return EXIT_FAILURE;
        }
        dup2(fd, STDIN_FILENO); // Перенаправление стандартного ввода на файл
        close(fd);
    }

    setjmp(begin); // Установка точки возврата
    endofshellint = endofshell(); // Проверка состояния завершения оболочки

    // Основной цикл работы программы
    while (!endofshellint) {
        printf("$ ");
        endofshellint = createlist(&ls); // Создание списка команд
        if (endofshellint) {
            shellexit(); // Завершение оболочки при необходимости
        }

        printlist(ls); // Вывод списка команд
        qur = ls; // Создание временного указателя на список
        if (!endofshellint) {
            t1 = buildtree(&qur); // Построение дерева команд
            ansrec = print_tree(t1, 2); // Вывод дерева команд с отступом
            shellwork(t1); // Выполнение команд
	    printf("Pipe recursion depth: %d\n", ansrec);
	    print_last_pid();
	    printf("#############################################################\n");
        }

        delete_tree(&t1);
        free(ls);
        ls = NULL;
        // Ожидание завершения всех дочерних процессов
        while (waitpid(-1, &stat, WNOHANG) > 0);
        endofshellint = endofshell(); // Проверка состояния завершения оболочки
    }

    setjmp(sexit); // Установка точки возврата для завершения
    if (t1 != NULL) {
        delete_tree(&t1);
    }
    if (ls != NULL) {
        free(ls);
    }
    printf("Successful completion of the shell\n");
    return EXIT_SUCCESS;
}
