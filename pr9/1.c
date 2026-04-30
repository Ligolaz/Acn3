#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <min_uid>\n", argv[0]);
		exit(1);
	}
	int min_uid = atoi(argv[1]);
	FILE *pipe;
	char line[256];
	char my_name[100] = "";

	//Get current username
	struct passwd *p = getpwuid(getuid());
	if (p) strncpy(my_name, p->pw_name, 99);

	//Open pipe to read passwd data
	pipe = popen("getent passwd", "r");
	if (!pipe) exit(1);

	while (fgets(line, sizeof(line), pipe)) {
		//Tokenize: user:x:uid:...
		char *user = strtok(line, ":");
		strtok(NULL, ":"); //Skip x
		char *uid_s = strtok(NULL, ":");
		if (!user || !uid_s) continue;

		int uid = atoi(uid_s);
		//Check if it is a regular user and not me
		if (uid >= min_uid && strcmp(user, my_name) != 0) {
			printf("Found: %s (UID: %d)\n", user, uid);
		}
	}
	pclose(pipe);
	return 0;
}
