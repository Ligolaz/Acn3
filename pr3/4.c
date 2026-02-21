#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void limit_reached(int n);

int main(){ 
	//Встановлено обробник сигналу про перевищення часу CPU
	signal(SIGXCPU, limit_reached);

	printf("Starting infinite loop to hit CPU time limit...\n");
	//this cycle must load one CPU core at 100%
	while(1);
	//This part shouldn't be completed cuz program is gonna get killed by a signal
	return 0; 
}

void limit_reached(int n){
	printf("\nCPU time limit exceeded! Terminating.\n");
	exit(1);
}