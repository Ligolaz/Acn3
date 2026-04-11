#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;
	pid = fork();
	//In case fork failed
	if (pid < 0) {
		printf("Forkn't\n");
		return 1;
	}
	//Will be executed in parent and child processes
	else if (pid > 0) { //Positive value (ID of child) - parent process
		printf("(Parent proc) Child ID: %d\n", pid);
	}
	else { //0 is child process
		printf("(Child proc) PID: %d\n", pid);
	}
}
