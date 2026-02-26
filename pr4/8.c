#include <stdio.h>
#include <stdlib.h>

void check_reuse(size_t);

int main(){
	//test for 32 bites
	printf("Small blocks (32 B)\n");
	check_reuse(32);
	//test for 1mb
	printf("Large blocks (1 MB)\n");
	check_reuse(1024 * 1024);
}

void check_reuse(size_t size){
	void *prev_ptr = NULL;
	int reused = 0;
	int i = 0;

	//5 allocs and 5 times freeing
	while(i++ < 5){
		void *ptr = malloc(size);
		printf("%d. ptr: %p", i, ptr);
		//check if new adress is the same as the previous one
		if(ptr == prev_ptr){
			printf(" (REUSED)");
			reused++;
		}
		printf("\n");
		//freeing memory so alloc could reuse it
		free(ptr);
		prev_ptr = ptr;
	}
	printf("Reused: %d times\n\n", reused);
}
