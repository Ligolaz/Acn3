#include <stdio.h>
#include <stdlib.h>

int main(){
	void *ptr = malloc(0);
	if(ptr == NULL){
		printf("Returned NULL\n");
	}
	else{
		printf("Returned pointer: %p\n", ptr);
		free(ptr);
	}
}
