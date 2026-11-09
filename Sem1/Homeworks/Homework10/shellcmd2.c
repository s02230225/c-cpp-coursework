/* CMD1 | (CMD2 && CMD3 < FILE4) | CMD5 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd1[2], fd2[2], f, status;
    pipe(fd1);
    if (fork() == 0) {
        dup2(fd1[1], 1);
        close(fd1[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    pipe(fd2);
    close(fd1[1]);
    wait(NULL);
    if (fork() == 0) {
        dup2(fd2[1], 1);
        close(fd2[1]);
        dup2(fd1[0], 0);
        close(fd1[0]);
        close(fd2[0]);
        if (fork() == 0) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            f = open(argv[4], O_RDONLY);
            dup2(f, 0);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        }
        else
            _exit(1);
    }

    close(fd2[1]);
    close(fd1[0]);
    wait(NULL);
    if (fork() == 0) {
        dup2(fd2[0], 0);
        close(fd2[0]);
        execlp(argv[5], argv[5], NULL);
        _exit(1);
    }
    close(fd2[0]);
    while (wait(&status) != -1) {
    }
    if (WIFEXITED(status)) {
        _exit(WEXITSTATUS(status));
    }
    else {
        _exit(1);
    }
}
