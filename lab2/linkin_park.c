#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
	struct stat file_data;
	char *soft = NULL;
	char *hard = NULL;
	int path_len = strlen(argv[1]);
	if (lstat(argv[1], &file_data) != 0) {
		perror("Something Bad: ");
		return -1;
	}

	if (S_ISREG(file_data.st_mode)) {
		printf("File Type: Regular file\n");

		// Create filenames
		hard = (char *)malloc(path_len + 5);
		sprintf(hard, "%s.hard", argv[1]);

		if (link(argv[1], hard) != 0) {
			perror("Error creating hard link: ");
			free(hard);
			return -1;
		}

		soft = (char *)malloc(path_len + 4);
		sprintf(soft, "%s.sym", argv[1]);
		if (symlink(argv[1], soft) != 0) {
			perror("Error creating hard link: ");
			free(soft);
			return -1;
		}

		free(soft);
		free(hard);
	}

	return 0;
} 