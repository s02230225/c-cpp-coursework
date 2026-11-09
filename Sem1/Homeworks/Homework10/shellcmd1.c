/* ( cmd1 < file1 && cmd2 ) | cmd3 >> file2 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd[2];
    int f, status;
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (fork() == 0) {
            f = open(argv[2], O_RDONLY);
            dup2(f, 0);
            close(f);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else
            _exit(1);
    }
    close(fd[1]);
    wait(NULL);
    if (fork() == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        f = open(argv[5], O_WRONLY | O_CREAT | O_APPEND);
        dup2(f, 1);
        close(f);
        execlp(argv[4], argv[4], NULL);
    }
    close(fd[0]);
    while (wait(&status) != -1) {
    }
    if (WIFEXITED(status)) {
        _exit(WEXITSTATUS(status));
    } else {
        _exit(1);
    }
}
