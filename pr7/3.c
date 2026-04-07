#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	//Check for keyword and filename
	if (argc < 3) return 1;
	FILE *f = fopen(argv[2], "r");
	if (!f) return 1;
	char line[512];
	//Looking for word in each line
	while (fgets(line, sizeof(line), f)) {
		if (strstr(line, argv[1])) printf("%s", line);
	}
	fclose(f);
	return 0;
}
