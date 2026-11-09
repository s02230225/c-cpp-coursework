/* n6_seq */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int n, i = 0;
	printf("Write down n: ");
	scanf("%d", &n);
	if (n <= 0)
		return 0;
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	else {	
		while(i++ != n-1) {
			if (fork() > 0)
				break;
	        }
		if (i == n) {
			printf("%d\n", i);
			_exit(0); 
		}
		else {
			printf("%d ", i);
			fflush(stdout);
		}
		wait(NULL);
		_exit(0);
	}
}
