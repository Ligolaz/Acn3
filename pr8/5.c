#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int p[2];
	pipe(p);
	char *msg = "Hello";
	char buf[100];

	//Writing only 5 bytes
	write(p[1], msg, strlen(msg));

	printf("Requested: 100 bytes from pipe\n");
	//Requesting 100, but only 5 are available
	ssize_t n = read(p[0], buf, 100);

	printf("Actually read: %ld bytes\n", n);
	printf("Reason: Pipe had only 5 bytes available at the moment\n");

	return 0;
}
