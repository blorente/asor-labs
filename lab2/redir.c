#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);

	if (fd == 0) {
		perror("");
	}
	dup2(fd, 1);
	printf("THis is supposed to go in the file\n");
	return 0;
}