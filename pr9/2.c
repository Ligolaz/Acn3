#include <stdlib.h>
#include <stdio.h>

int main() {
	//Using sudo to read shadow file where encrypted passwords are kept
	int res = system("sudo cat /etc/shadow");
	//Return error if execution failed
	if (res == -1) {
		printf("Exec failed\n");
		return 1;
	}
	return 0;
}
