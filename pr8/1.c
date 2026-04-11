#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
	int p[2];
	pipe(p);
	//Setting pipe write end to non-blocking mode
	fcntl(p[1], F_SETFL, O_NONBLOCK);

	char buf[100000];
	memset(buf, 'A', sizeof(buf));
	//Trying to write more than pipe buffer capacity (usually 64KB)
	ssize_t count = write(p[1], buf, sizeof(buf));

	printf("Requested: %ld, Written: %ld\n", sizeof(buf), count);
	return 0;
}
