#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_COUNT 4
#define ARRAY_SIZE 1000

//Func that will be executed by every thread
void* memory_worker(void* arg) {
	long id = (long)arg;

	//Mem alloc in Heap
	int *data = (int*)malloc(ARRAY_SIZE * sizeof(int));
	if (data == NULL) {
		printf("Thread %ld: Malloc failed\n", id);
		return NULL;
	}

	//Printing adress of selected thread
	printf("Thread %ld: Allocated memory at address: %p\n", id, (void*)data);
	//Filling data
	for (int i = 0; i < ARRAY_SIZE; i++) {
		data[i] = id;
	}
	sleep(1);

	//Check for files safety
	if (data[0] != id || data[ARRAY_SIZE - 1] != id) {
		printf("Thread %ld: Data corruption detected!\n", id);
	} else {
		printf("Thread %ld: Data verified successfully. Freeing memory.\n", id);
	}
	//Clearing data
	free(data);
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t threads[THREAD_COUNT];
	printf("Starting %d threads to test memory allocation...\n", THREAD_COUNT);
	//Creating threads
	for (long i = 0; i < THREAD_COUNT; i++) {
		if (pthread_create(&threads[i], NULL, memory_worker, (void*)i) != 0) {
			printf("Error creating thread %ld\n", i);
			return EXIT_FAILURE;
		}
	}
	//Waiting till the end
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("All threads finished execution.\n");
	return EXIT_SUCCESS;
}
