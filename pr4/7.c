#include <stdio.h>
#include <stdlib.h>

struct sbar{int a; int b;};

int main(){
	struct sbar *ptr, *newptr;
	//array for 1k elements
	ptr = calloc(1000, sizeof(struct sbar));
	if(!ptr){
		printf("Didn't calloc\n");
		exit(1);
	}
	printf("Callocated ptr: %p\n", ptr);

	//array getting smaller down to 500
	newptr = reallocarray(ptr, 500, sizeof(struct sbar));
	if(!newptr){
		printf("Didn't reallocarray\n");
		free(ptr);
		exit(1);
	}
	printf("Reallocarray'd newptr: %p\n", newptr);
	free(newptr);
}
