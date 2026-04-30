#include <stdio.h>
#include <stdlib.h>

int main() {
	const char *u = "user";
	const char *f = "/tmp/orig.txt";
	const char *c = "/home/user/copy.txt";

	printf("Creating file as user...\n");
	system("echo 'Secret data' > /tmp/orig.txt");

	//Root copies to home and locks permissions
	printf("Copying to home as root...\n");
	char cmd[512];
	snprintf(cmd, sizeof(cmd), "sudo cp %s %s && sudo chown root:root %s && sudo chmod 444 %s", f, c, c, c);
	system(cmd);

	//User tries to edit
	printf("User trying to edit...\n");
	snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c 'echo more >> %s' 2>/dev/null", u, c);
	if (system(cmd) != 0) printf("Edit denied\n");

	//User tries to delete
	printf("User trying to delete...\n");
	snprintf(cmd, sizeof(cmd), "sudo -u %s rm %s", u, c);
	if (system(cmd) == 0) printf("Deleted successfully (dir perms allowed it)\n");
	return 0;
}
