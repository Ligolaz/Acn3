#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
	DIR *d = opendir(".");
	struct dirent *de;
	struct stat s;
	if (!d) return 1;
	while ((de = readdir(d))) {
		if (de->d_name[0] == '.') continue;
		stat(de->d_name, &s);
		//Printing file type and permissions manually
		printf((S_ISDIR(s.st_mode)) ? "d" : "-");
		printf((s.st_mode & S_IRUSR) ? "r" : "-");
		printf((s.st_mode & S_IWUSR) ? "w" : "-");
		printf((s.st_mode & S_IXUSR) ? "x" : "-");
		//Links, User, Group, Size, Name
		printf(" %ld %s %s %ld %s\n", s.st_nlink, getpwuid(s.st_uid)->pw_name, getgrgid(s.st_gid)->gr_name, s.st_size, de->d_name);
	}
	closedir(d);
	return 0;
}
