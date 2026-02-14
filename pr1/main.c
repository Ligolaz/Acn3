#include <stdio.h>
#include <pthread.h>
#include "module1.h"
#include "module2.h"

int main() {
	pthread_t thread1, thread2;

	printf("Main - starting threads...\n");
	//creating and launching threads
	pthread_create(&thread1, NULL, do_work_module1, NULL);
	pthread_create(&thread2, NULL, do_work_module2, NULL);
	//waiting till threads finish their work
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Main - all threads have finished.\n");
	return 0;
}
