#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void xa_xb(int, int);

int main(){
	//without overflow
	xa_xb(100, 200);
	//overflow int
	xa_xb(INT_MAX, 2);
}

void xa_xb(int xa, int xb){
	int num = xa * xb;
	size_t num_sizet = (size_t)num;
	printf("xa: %d, xb: %d\n", xa, xb);
	printf("num: %d\n", num);
	printf("num_sizet = %zu\n", num_sizet);

	void *ptr = malloc(num);
	if (ptr){
		printf("Allocated %zu bytes\n\n", num_sizet);
		free(ptr);
	}
	else{
		printf("Didn't allocate %zu bytes\n\n", num_sizet);
	}
}
