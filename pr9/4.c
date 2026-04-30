#include <stdio.h>
#include <stdlib.h>

int main() {
	//Displaying current username
	printf("Running whoami:\n");
	system("whoami");
	//Displaying UID, GID and groups
	printf("\nRunning id:\n");
	system("id");
	return 0;
}
