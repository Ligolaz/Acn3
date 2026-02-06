#include <stdio.h>

void input();
void output();
void process1(); //gonna be in /usr/lib
void process();  //gonna be in ~/mylibs

int main() {
	printf("Starting program...\n");
	input();
	process1();
	process();
	output();
	printf("Ending Program.\n");
	return 0;
}
