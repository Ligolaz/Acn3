#include <stdio.h>
#include <stdlib.h>

int main(){
	//should be working like malloc(10)
	void *ptr = realloc(NULL, 10);
	if(!ptr){
		printf("Didn't reallocate ptr\n");
		exit(1);
	}
	else{
		printf("Reallocated ptr with NULL: %p\n", ptr);
	}

	//realloc(ptr, 0) works like malloc(0) - returns NULL or a pointer
	void *ptr1 = realloc(ptr, 0);
	if(!ptr1){
		printf("realloc with 0 size ptr1 is NULL\n");
	}
	else{
		printf("realloc with 0 size ptr1 is %p\n", ptr1);
	}

	if(ptr1){
		free(ptr1);
	}
}
