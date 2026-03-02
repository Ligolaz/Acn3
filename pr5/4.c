#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Allocating memory (small chunk for tcache)...\n");
	//Allocating just a little aount of mem(16bites) just to get into a tcache
	int *ptr = (int*)malloc(sizeof(int));
	*ptr = 42;
	printf("Address: %p\n", (void*)ptr);

	printf("First free...\n");
	free(ptr); //Pointer get's into tcache

	printf("Second free (Double Free)...\n");
	//Freeing second time. In nowdays system this would lead to error, but Valgrind gonna catch it 
	free(ptr); 

	printf("Program finished (this might not be reached due to crash)\n");
	return 0;
}
