#include <stdio.h>
#include <dirent.h>
#include <string.h>

void scan(const char *p) {
	DIR *d = opendir(p);
	if (!d) return;
	struct dirent *de;
	while ((de = readdir(d))) {
		if (de->d_name[0] == '.') continue;
		char path[1024];
		snprintf(path, sizeof(path), "%s/%s", p, de->d_name);
		printf("%s\n", path);
		//If it is a folder - scan it too
		if (de->d_type == DT_DIR) scan(path);
	}
	closedir(d);
}

int main() {
	scan(".");
	return 0;
}
