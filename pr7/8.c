#include <stdio.h>
#include <dirent.h>

int main() {
	DIR *d = opendir(".");
	struct dirent *de;
	while ((de = readdir(d))) {
		//Only regular files
		if (de->d_type == DT_REG) {
			printf("Delete %s? (y/n): ", de->d_name);
			if (getchar() == 'y') remove(de->d_name);
			while (getchar() != '\n');
		}
	}
	return 0;
}
