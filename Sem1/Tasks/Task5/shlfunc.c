#include "shlfunc.h"

static int _eos = 0; // Статическая переменная для отслеживания состояния завершения оболочки
static int last_pid = -1;

int endofshell(){
    return _eos; // Возвращает текущее состояние завершения
}

void shellexit(){
    _eos = 1; // Устанавливает состояние завершения оболочки
} 

// Функция для вывода PID последнего выполненного процесса
void print_last_pid() {
    if (last_pid != -1) {
        printf("Last executed process PID: %d\n", last_pid);
    } else {
        printf("No processes have been executed yet.\n");
    }
}

int pwd(){
    char buf[1024];
    if(getcwd(buf, 1024) == NULL) // Получаем текущий рабочий каталог
        error("PWD ERROR");
    else 
        printf("%s\n",buf);
    return 0;
}

void shellcd(char *dirpath){
    char buf[1024];
    if (dirpath == NULL)
        chdir(getenv("HOME"));
    else if (realpath(dirpath,buf) == NULL) // Проверяем, является ли указанный путь действительным
        error("CANT GET PATH");
    else 
        chdir(buf);
}

void _changein(tree t){
    int fd;
    if (t->infile == NULL) return;
    fd = open(t->infile, O_RDONLY); // Открываем файл для чтения
    if (fd == -1) error("CANT OPEN FILE");
    dup2(fd,0); // Перенаправляем входной поток на файл
    close(fd); // Закрываем дескриптор файла
}

void _changeout(tree t){
    int fd;
    if (t->outfile == NULL) return;
    // Открываем файл для записи (в зависимости от режима - добавление или перезапись)
    if (t->append == 0) 
        fd = open(t->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    else 
        fd = open(t->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);
    
    if (fd == -1) error("CANT OPEN FILE");
    dup2(fd,1); // Перенаправляем выходной поток на файл
    close(fd); // Закрываем дескриптор файла
}

void changeinout(tree t){
    _changein(t);
    _changeout(t);
}

int progrun(tree t, int flag){
    list ls = t->argv;
    int child_pid, status = 0, fd[2]; // Переменные для хранения идентификатора дочернего процесса и статуса
    if (ls != NULL){ // Если есть аргументы
        if(isexit(ls[0])) { // Проверяем, является ли команда "exit"
            shellexit();
        }
        else if(iscd(ls[0])) 
            shellcd(ls[1]); // Выполняем команду "cd"
        else if(ispwd(ls[0])) { // Если команда "pwd"
            if ((child_pid = fork()) == 0){ // Создаем дочерний процесс
                changeinout(t); // Изменяем потоки
                if (pwd() == -1) perror("Cant get path"); // Получаем текущий путь
                exit(0); // Завершаем процесс
            }
            else if(child_pid == -1 ) error("FORK RUN"); // Обработка ошибки fork
            status = waitpid(child_pid,&status,0) == child_pid && WIFEXITED(status); // Ожидаем завершения дочернего процесса
	    last_pid = child_pid;
        }
        else{
            if ((child_pid = fork()) == 0){ // Создаем дочерний процесс
                // Обработка фонового выполнения и перенаправления потока
                if (t->backgrnd == 1 && flag && t->infile){
                    pipe(fd); // Создаем канал
                    close(fd[1]); // Закрываем конец записи
                    dup2(fd[0],0); // Перенаправляем входной поток
                    close(fd[0]); // Закрываем конец чтения
                }
                else if (t->backgrnd == 0) signal(SIGINT,SIG_DFL); // Восстанавливаем обработчик сигнала прерывания
                changeinout(t); // Изменяем потоки
                if (execvp(ls[0], ls) == -1) perror("Could not execve"); // Запускаем программу
                exit(1); // Завершаем процесс с ошибкой
            }
            else if(child_pid == -1 ) error("FORK RUN"); // Обработка ошибки fork
	    last_pid = child_pid;
            if (t->backgrnd == 0) { // Если не фоновой
                if (!issleep(t->argv[0])) signal(SIGTERM,SIG_DFL); // Восстанавливаем обработчик сигнала завершения
                status = (waitpid(child_pid,&status,0)) == child_pid && WIFEXITED(status); // Ожидаем завершения дочернего процесса
            }
        }
    }
    return status;
}

// Функция для обработки пайпов
int convwork(tree t, int flag){
    int fd[2], pipe_pid, status, nextstatus = -1, child_pid; // Переменные для работы с каналами и процессами
    pipe(fd); // Создаем канал
    if (t->pipe != NULL){ // Если есть пайп
        if((child_pid = fork()) == 0){ // Создаем дочерний процесс
            signal(SIGTERM,SIG_IGN); // Игнорируем сигнал завершения
            pipe(fd); // Создаем новый канал
            if ((pipe_pid = fork()) == 0){ // Создаем первый процесс
                close(fd[0]); // Закрываем конец чтения
                dup2(fd[1],1); // Перенаправляем выходной поток
                close(fd[1]); // Закрываем конец записи
                changeinout(t); // Изменяем потоки
                if(t->argv != NULL){
                    progrun(t,flag); // Запускаем программу
                }
                if(t->psubcmd != NULL){
                    status = shellwork(t->psubcmd); // Запускаем подкоманду
                    exit(status); // Завершаем с соответствующим статусом
                }
                exit(1); // Завершаем процесс с ошибкой
            }
            else if (pipe_pid == -1) error("CONV FORK ERROR"); // Обработка ошибки fork

            close(fd[1]); // Закрываем конец записи
            dup2(fd[0],0); // Перенаправляем входной поток
            close(fd[0]); // Закрываем конец чтения
            nextstatus = convwork(t->pipe,0); // Обрабатываем следующий пайп
            kill(pipe_pid,SIGTERM); // Завершаем первый процесс
            if(waitpid(pipe_pid,&status,0) == pipe_pid && WIFEXITED(status)){
                nextstatus = WEXITSTATUS(status); // Получаем статус завершения
            }
            exit(nextstatus); // Завершаем с соответствующим статусом
        }
        else if(child_pid == -1 ) error("FORK ERORR"); // Обработка ошибки fork
        if(t->backgrnd == 0){ // Если не фоновой
            if(waitpid(child_pid,&status,0) == child_pid && WIFEXITED(status)){
                nextstatus = WEXITSTATUS(status); // Получаем статус завершения
            }
            else nextstatus = 0; // Если произошла ошибка
        }
        return nextstatus; // Возвращаем статус выполнения
    }
    else{
        return shellwork(t); // Если нет пайпов, выполняем команду
    }
    return nextstatus; // Возвращаем статус выполнения
}

// Основная функция обработки командной оболочки
int shellwork(tree t){
    int child_pid, status, nextstatus =1, flag = 0; // Переменные для работы с процессами и статусами

    if (t == NULL) return 0; // Если дерево команд пустое, возвращаем 0
    flag = t->backgrnd; // Получаем флаг фонового выполнения
    if (t->pipe != NULL){ // Если есть пайп
        status = convwork(t, flag); // Обрабатываем пайп
    }
    if (t->next != NULL){ // Если есть следующая команда
        if (t->pipe == NULL){ // Если нет пайпов
            if(t->argv != NULL){
                status = progrun(t,t->backgrnd); // Запускаем программу
            }
            else if(t->psubcmd != NULL){ // Если есть подкоманда
                if(fork()==0){ // Создаем дочерний процесс
                    status = shellwork(t->psubcmd); // Запускаем подкоманду
                    exit(status); // Завершаем процесс с соответствующим статусом
                }
            }
        }
        if(t->type == NXT){ // Если тип команды - NEXT
            return shellwork(t->next); // Обрабатываем следующую команду
        }
        else if(t->type == OR && nextstatus ==0){ // Если тип команды - OR и предыдущий статус 0
            return shellwork(t->next); // Обрабатываем следующую команду
        }
        else if(t->type == AND && nextstatus != 0){ // Если тип команды - AND и предыдущий статус не 0
            return shellwork(t->next); // Обрабатываем следующую команду
        }
        else return -1; // Возвращаем -1, если условия не выполнены
    }
    // Если есть подкоманда и нет других команд
    if (t->psubcmd != NULL && t->pipe == NULL && t->next == NULL){
        if((child_pid = fork()) == 0){ // Создаем дочерний процесс
            changeinout(t); // Изменяем потоки
            status = shellwork(t->psubcmd); // Запускаем подкоманду
            exit(status); // Завершаем процесс с соответствующим статусом
        }
        else if(child_pid == -1 ) error("FORK ERORR"); // Обработка ошибки fork
        if(t->backgrnd == 0){ // Если не фоновой
            if(waitpid(child_pid,&status,0) == child_pid && WIFEXITED(status)){
                nextstatus = WEXITSTATUS(status); // Получаем статус завершения
            }
            else nextstatus = 0; // Если произошла ошибка
        }
    }
    // Если есть аргументы и нет пайпов, следующих команд и подкоманд
    if (t->argv != NULL && t->pipe == NULL && t->next == NULL && t->psubcmd == NULL){
        return progrun(t,t->backgrnd); // Запускаем программу
    }
    return nextstatus; // Возвращаем статус выполнения
}
