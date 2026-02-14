#include <stdio.h>
#include <unistd.h>
#include "module2.h"

void* do_work_module2(void* arg) {
	printf("Module 2 - another 2sec work...\n");
        sleep(2);
	printf("Module 2 - work finished.\n");
	return NULL;
}
