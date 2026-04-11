#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

void run_test(int n, const char* label) {
	int *arr = malloc(n * sizeof(int));
	for(int i=0; i<n; i++) arr[i] = rand();

	clock_t start = clock();
	qsort(arr, n, sizeof(int), cmp);
	double t = (double)(clock() - start) / CLOCKS_PER_SEC;

	printf("%s (n=%d): %.3f sec\n", label, n, t);
	free(arr);
}

int main() {
	srand(time(NULL));
	//Testing different sizes to see growth
	run_test(100000, "Small");
	run_test(1000000, "Large");
	return 0;
}
