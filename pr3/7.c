#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){
	int count = 0;

	printf("Stress testing process limit (ulimit -u)...\n");
	while(1){
		//New process
		pid_t pid = fork();

		//If fork returned -1 - limit was reached
		if(pid < 0){
			printf("\nLimit reached so fork failed.\n");
			printf("Successfully created %d child processes.\n", count);
			printf("The rest of the limit is likely taken by system processes.\n");
			exit(0);
		}
		//If it's child process - it's must be active so it would take space amoung processes
		if(pid == 0){
			//Process lasts for 10sec for the test, then we're killing it
			sleep(10);
			exit(0);
		}
		//If it's parent process - increasing counter by 1
		count++;
		//Number of created process (every 50 times so it looks a bit cleaner)
		if(count % 50 == 0) {
			printf("Created %d processes...\n", count);
		}
	}
	return 0;
}