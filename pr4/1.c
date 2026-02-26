#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//depends if prog would be compiled in 32 or 64 bit
#define BITS_SIZET sizeof(size_t) * 8

int main(){
	printf("Bits in size_t: %ld\n", BITS_SIZET);

	size_t max_sizet = pow(2, BITS_SIZET);
	printf("Max size_t (2^%ld): %zu bytes\n", BITS_SIZET, max_sizet);
	//Exabyte 1024^6 of bytes
	size_t exb = max_sizet / (pow(1024, 6));
	printf("malloc(3) can allocate %zu EB or %zu B max\n", exb, max_sizet);
}
