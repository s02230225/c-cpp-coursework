/* n8_duplicate */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
	if (argc != 2) {
		fprintf(stderr, "Wrong number of args! Usage: <filename>\n");
		return 1;
	}
	int fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "Error in opening file\n");
		return 1;
	}
	int fsize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char buf4[4];
	for (int i = 0; i < fsize/4; ++i) {
		read(fd, &buf4, 4);
		lseek(fd, fsize-4, SEEK_CUR);
		write(fd, &buf4, 4);
		lseek(fd, 4*(i+1), SEEK_SET);
	}
	close(fd);
	return 0;
}
