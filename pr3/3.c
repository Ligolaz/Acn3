#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void limit_reached(int);

int main(){
	FILE *file;
	int roll;
	//Processing of the SIGXFSZ signal (CPU timeout)
	signal(SIGXFSZ, limit_reached);
	srand(time(NULL));
	file = fopen("rolls.txt", "w");
	if(file == NULL){
		printf("Can't open the file\n");
		exit(1);
	}

	while(1){
		roll = (rand() % 6) + 1;
		if(fprintf(file, "rolled %d\n", roll) < 0){
			printf("Can't write down\n");
			break;
		}
		fflush(file);
	}
	fclose(file);
}

void limit_reached(int n){
	printf("Limit was reached so imma stop\n");
	exit(1);
}