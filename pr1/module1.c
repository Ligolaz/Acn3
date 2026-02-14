#include <stdio.h>
#include <unistd.h>
#include "module1.h"

void* do_work_module1(void* arg) {
	printf("Module 1 - 2 sec work...\n");
	sleep(2);
	printf("Module 1 - work finished.\n");
	return NULL;
}
