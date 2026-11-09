/* n3_macro */
#include <stdio.h>
#define MY_WIFEXITED(status) (((status) & 0x7F) ? 0 : 1)
#define MY_WEXITSTATUS(status) (((status) & 0xFF00) >> 8)
#define MY_WIFSIGNALED(status) (((status) & 0x7F) ? 1 : 0)
#define MY_WTERMSIG(status) ((status) & 0x7F)

void res(int status) {
	printf("If exited: %d; Code = %d\n", MY_WIFEXITED(status), MY_WEXITSTATUS(status));
	printf("If stopped by signal: %d; Code = %d\n", MY_WIFSIGNALED(status), MY_WTERMSIG(status));
}

int main() {
	res(0x0180);
	res(0x0085);
	return 0;
}
