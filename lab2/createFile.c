#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char **argv) {
	int prev = umask(0077);
	int fd = open(
		argv[1],
		O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH);
	umask(prev);

	printf("File created at %s, with file descriptor %i\n", argv[1], fd);
	return close(fd);
}