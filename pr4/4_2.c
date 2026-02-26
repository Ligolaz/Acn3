#include <stdio.h>
#include <stdlib.h>

int main(){
	void *ptr = NULL;
	int i = 0;
	while(i++ < 3){
		if(!ptr)
			ptr = malloc(1);

		printf("%d. ptr: %p\n", i, ptr);
		((char*)ptr)[0] = 'e';
		free(ptr);
		//second iteration - (!ptr) gonna be executed, memory will be allocated without uaf
		ptr = NULL;
	}
}
