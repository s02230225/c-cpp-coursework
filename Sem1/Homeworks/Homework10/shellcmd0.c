/* { cmd1 || cmd2 } && cmd3 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 4) _exit(1);

    pid_t pid1;
    int status;
    if ((pid1 = fork()) == 0) {
        pid_t pid2;
        if ((pid2 = fork()) == 0) {
            execlp(argv[1], argv[1], (char*)0);
            _exit(1);
        }
        else if (pid2 > 0) {
            wait(&status);
            if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                execlp(argv[2], argv[2], (char*)0);
                _exit(1);
            }
            else {
                _exit(0);
            }
        }
    }
    else if (pid1 > 0) {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            execlp(argv[3], argv[3], (char*)0);
            _exit(1);
        }
        else
            _exit(1);
    }
}
