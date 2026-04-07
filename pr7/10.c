#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	//Random 0.0 to 1.0
	printf("Rand 0-1: %f\n", (double)rand() / RAND_MAX);
	//Random 0.0 to N
	double n = 100.0;
	printf("Rand 0-%.1f: %f\n", n, ((double)rand() / RAND_MAX) * n);
	return 0;
}
