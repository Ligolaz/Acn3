#include <stdio.h>
#include <time.h>

int main() {
	clock_t t = clock();
	//Empty loop to waste some time
	for (long i = 0; i < 100000000; i++);
	t = clock() - t;
	//Show time in milliseconds
	printf("Work done in: %.2f ms\n", ((double)t * 1000) / CLOCKS_PER_SEC);
	return 0;
}
