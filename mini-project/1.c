#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

//Function to set resource limits
void set_limit(int resource, long value) {
	struct rlimit rl;
	if (getrlimit(resource, &rl) == -1) { //Get current limits first
		perror("getrlimit");
		exit(1);
	}
	//Set soft and hard limits
	rl.rlim_cur = value;
	rl.rlim_max = value;
	if (setrlimit(resource, &rl) == -1) { //Now setting em'
		perror("setrlimit");
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <cpu|mem|files> <value> <command> (args...)\n", argv[0]);
		return 1;
	}

	char *type = argv[1];
	long limit_val = atol(argv[2]);
	char **cmd_args = &argv[3];

	pid_t pid = fork(); //Cloning so this code is executed by two(parent, child) processes at the same time

	if (pid < 0) { //If system doesn't have enough resources
		perror("fork");
		return 1;
	}

	if (pid == 0) { //If 0 than it's child process
		//Apply selected limit before execution
		if (strcmp(type, "cpu") == 0) {
			set_limit(RLIMIT_CPU, limit_val); //Value in seconds
		} else if (strcmp(type, "mem") == 0) {
			set_limit(RLIMIT_AS, limit_val);  //Value in bytes
		} else if (strcmp(type, "files") == 0) {
			set_limit(RLIMIT_NOFILE, limit_val); //Max opened files at the same time
		} else {
			fprintf(stderr, "Unknown limit type\n");
			exit(1);
		}

		//Replace child current program(literally this one) with the target program
		execvp(cmd_args[0], cmd_args);
		perror("execvp");
		exit(1);
	} else { //If not 0, than it's parent
		int status;
		waitpid(pid, &status, 0); //After child dies info abt that will be in "status"

		if (WIFEXITED(status)) {
			fprintf(stderr, "\n(Parent) Child exited with code: %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			fprintf(stderr, "\n(Parent) Child killed by signal: %d (%s)\n", WTERMSIG(status), strsignal(WTERMSIG(status))); //Without strsingal - just number, and with - full message
		}
	}
	return 0;
}