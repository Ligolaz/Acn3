#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd = open("test.dat", O_RDWR | O_CREAT | O_TRUNC, 0600);
	unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
	write(fd, data, sizeof(data));

	//Moving pointer to the 3rd byte (index 3)
	lseek(fd, 3, SEEK_SET);
	unsigned char buf[4];
	//Reading 4 bytes from current position
	read(fd, buf, 4);

	printf("Buff contains: ");
	for(int i=0; i<4; i++) printf("%d ", buf[i]);
	printf("\n");

	close(fd);
	unlink("test.dat");
	return 0;
}
