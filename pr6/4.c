#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE (100 * 1024 * 1024) // 100mb
#define PAGE 4096 //4kb page size Стандартний розмір сторінки пам'яті

int main() {
	//Allocate and initialize memory to ensure that it exists physically
	char *ptr = malloc(SIZE);
	for(int i = 0; i < SIZE; i += PAGE) ptr[i] = 'A';

	//Fork creates a child sharing the same memory (Copy on Write thing)
	if (fork() == 0) {
		// Writing to memory triggers Copy-on-Write
		//OS detects the write attempt and copies pages and that's causing page-faults
		for(int i = 0; i < SIZE; i += PAGE) ptr[i] = 'B';
	} else {
		//Parent waits for child to finish
		wait(NULL); // Просто чекаємо
	}
	free(ptr);
}
