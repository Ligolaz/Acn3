#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
	//Open file for writing
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) exit(1);

	if (fork() == 0) {
		//Child writes its message
		write(fd, "Child data\n", 11);
		exit(0);
	} else {
		//Parent waits and writes its message
		wait(NULL);
		write(fd, "Parent data\n", 12);
		close(fd);
	}

	//Show final file content
	printf("File content:\n");
	system("cat output.txt");
	return 0;
}
