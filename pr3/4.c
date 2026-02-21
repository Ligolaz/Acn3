#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void limit_reached(int);
void lottery(int *, int, int);
void print_nums(int *, int);

int main(){
	//CPU timeout signal catcher
	signal(SIGXCPU, limit_reached);
	srand(time(NULL));
	int res_49[7];
	int res_36[6];

	//Main task (that's not enough for signal)
	lottery(res_49, 7, 49);
	lottery(res_36, 6, 36);
	printf("7 із 49: ");
	print_nums(res_49, 7);
	printf("6 із 36: ");
	print_nums(res_36, 6);

	printf("Simulating massive lottery calculations to hit CPU limit...\n");
	//Additionally loading system by generating
	//lottery inf till the system won't send the SIGXCPU
	while(1){
		int dummy[7];
		lottery(dummy, 7, 49);
	}  
	return 0;
}

void lottery(int *arr, int n, int max){
	int used[max + 1];
	for(int i=0; i <= max; i++){
		used[i] = 0;
	}
	int count = 0;
	while(count < n){
		int num = (rand() % max) + 1;
		if(!used[num]){
			arr[count++] = num;
			used[num] = 1;
		}
	}
}

void print_nums(int *arr, int n){
	for(int i=0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void limit_reached(int n){
	printf("\CPU is down. (SIGXCPU)\n");
	exit(1);
}