#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
	struct stat file_data;
	char time_pretty[20];

	if (lstat(argv[1], &file_data) != 0) {
		perror("Something Bad: ");
		return -1;
	}

	printf("Major: %i\n", (unsigned int)major(file_data.st_dev));
	printf("Minor: %i\n", (unsigned int)minor(file_data.st_dev));
	printf("Inode number: %i\n", (unsigned int)file_data.st_ino);

	if (S_ISLNK(file_data.st_mode)) {
		printf("File Type: Symbolic link\n");
	} else if (S_ISDIR(file_data.st_mode)) {
		printf("File Type: Directory\n");
	} else if (S_ISREG(file_data.st_mode)) {
		printf("File Type: Regular file\n");		
	} else {
		printf("File Type: Unrecognized\n");
	}

	time_t access_time = file_data.st_atime;
	strftime(time_pretty, 20, "%Y-%m-%d %H:%M:%S", localtime(&access_time));
	printf("Last accessed: %s\n", time_pretty);	
	return 0;
}