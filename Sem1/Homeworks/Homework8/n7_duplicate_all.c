/* n7_duplicate_all */
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
	char c;
	for (int i = 0; i < fsize; ++i) {
		read(fd, &c, 1);
		lseek(fd, fsize-1, SEEK_CUR);
		write(fd, &c, 1);
		lseek(fd, i+1, SEEK_SET);
	}
	close(fd);
	return 0;
}
