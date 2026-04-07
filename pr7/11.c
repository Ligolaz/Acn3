#include <stdio.h>

typedef enum { PENDING, RUNNING, PAUSED, DONE } State;
typedef struct { int id; State state; } Job;

Job q[3];
const char* st[] = {"Pending", "Running", "Paused", "Done"};

void status() {
	for (int i = 0; i < 3; i++) printf("Job %d is %s\n", q[i].id, st[q[i].state]);
	printf("---\n");
}

int main() {
	for (int i = 0; i < 3; i++) q[i] = (Job){i + 1, PENDING};
	printf("Queue Ready:\n");
	status();
	//Simulate job flow manually
	printf("Starting Job 1...\n");
	q[0].state = RUNNING;
	status();

	printf("Pausing Job 2 and finishing Job 1...\n");
	q[1].state = PAUSED;
	q[0].state = DONE;
	status();

	printf("Resuming Job 2...\n");
	q[1].state = RUNNING;
	status();
	return 0;
}
