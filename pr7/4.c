#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) return 1;
	for (int i = 1; i < argc; i++) {
		FILE *f = fopen(argv[i], "r");
		if (!f) continue;
		char line[256];
		int n = 0;
		printf("--- File: %s ---\n", argv[i]);
		while (fgets(line, sizeof(line), f)) {
			printf("%s", line);
			//Stop every 5 lines for demo
			if (++n % 5 == 0) {
				printf("[Press Enter]");
				getchar();
			}
		}
		fclose(f);
	}
	return 0;
}
