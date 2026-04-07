#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int sort_alpha(const void *a, const void *b) {
	return strcmp(*(char**)a, *(char**)b);
}

int main() {
	DIR *d = opendir(".");
	struct dirent *de;
	char *list[100];
	int n = 0;
	while ((de = readdir(d))) {
		//Only folders
		if (de->d_type == DT_DIR && de->d_name[0] != '.') list[n++] = strdup(de->d_name);
	}
	qsort(list, n, sizeof(char*), sort_alpha);
	for (int i = 0; i < n; i++) printf("%s\n", list[i]);
	return 0;
}
