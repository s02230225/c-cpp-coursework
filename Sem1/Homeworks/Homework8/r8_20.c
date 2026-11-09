/* r8_20 */
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

enum{ N = 2 };

int main(int argc, char** argv){
	if (argc != N+1) {
		fprintf(stderr, "Wrong number of args!\n");
		_exit(1);
	}
	if (fork() > 0) {
		int status;
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
			printf("Starting 2nd proccess\n");
			execl(argv[2], argv[2], (char*) 0);
			_exit(1);
		}
	}
	else {
		printf("Starting 1st proccess\n");
		execl(argv[1], argv[1], (char*) 0);
		_exit(1);
	}
	_exit(1);
}
