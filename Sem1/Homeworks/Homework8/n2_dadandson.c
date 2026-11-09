/* n2_dadandson */
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	if (fork() > 0){
		int x, status;
		int* buf = &x;
		int fd = open("fas_bin", O_CREAT | O_WRONLY);
		x = getpid();
		write(fd, buf, sizeof(int));
		close(fd);
		wait(&status);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			fd = open("fas_bin", O_RDONLY);
			read(fd, buf, sizeof(int));
			printf("Father pid is %d\n", x);
			lseek(fd, sizeof(int), SEEK_SET);
			read(fd, buf, sizeof(int));
			printf("Son pid is %d\n", x);
			close(fd);
			_exit(0);
		}
		else {
			fprintf(stderr, "Error in son\n");
			_exit(1);
		}
	}
	else {
		int x;
		int* buf = &x;
		int fd = open("fas_bin", O_CREAT | O_WRONLY);
		x = getpid();
		lseek(fd, sizeof(int), SEEK_SET);
		write(fd, buf, sizeof(int));
		close(fd);
		_exit(0);
	}
}	
