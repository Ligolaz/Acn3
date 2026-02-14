#include <stdio.h>
#include <omp.h> //OpenMP
#include "module1.h"
#include "module2.h"

int main() {
	printf("Main(OMP) - starting parallel sections...\n");
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			do_work_module1(NULL);
		}
		#pragma omp section
		{
			do_work_module2(NULL);
		}
	}
	printf("Main(OMP) - all sections finished.\n");
	return 0;
}
