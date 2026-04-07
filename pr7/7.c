#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
	DIR *d = opendir(".");
	struct dirent *de;
	while ((de = readdir(d))) {
		//Process only .c files
		if (strstr(de->d_name, ".c")) {
			printf("Found %s. Add read for others? (y/n): ", de->d_name);
			if (getchar() == 'y') {
				struct stat s;
				stat(de->d_name, &s);
				//Applying chmod with S_IROTH bit
				chmod(de->d_name, s.st_mode | S_IROTH);
			}
			while (getchar() != '\n');
		}
	}
	return 0;
}
