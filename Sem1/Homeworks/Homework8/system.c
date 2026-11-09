/* system */
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

int system(const char *command){
	if (command == NULL) {
		int fd = open("/etc/shells", O_RDONLY);
		if (fd == -1)
			return 0;
		int fsize = lseek(fd, 0, SEEK_END);
		if (close(fd) == -1)
			return 0;
		if (fsize > 34)
			return 1;
		else
			return 0;
	}
	else {
		pid_t pid;
        pid = fork();
		if (pid < 0)
			return -1;
		else if (pid > 0) {
			int status;
			waitpid(pid, &status, 1);
			if (WIFEXITED(status))
				return WEXITSTATUS(status);
			else
				return -1;
		}
		else {
			int tmp;
			tmp = execl("/bin/sh", "sh", "-c", command, (char *) NULL);
			if (tmp == -1)
				_exit(127);
			_exit(errno);
		}
	}
}

int main() {
    return 0;
}