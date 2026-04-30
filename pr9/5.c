#include <stdio.h>
#include <stdlib.h>

int main() {
	const char *u = "user";
	const char *f = "/tmp/test.txt";

	printf("Creating file...\n");
	system("echo 'Hello' > /tmp/test.txt");

	//Root sets owner and 640 perms (Group read only)
	printf("Root taking ownership, perms 640...\n");
	char cmd[256];
	snprintf(cmd, sizeof(cmd), "sudo chown root:sudo %s && sudo chmod 640 %s", f, f);
	system(cmd);

	//Check read
	printf("Testing read for %s:\n", u);
	snprintf(cmd, sizeof(cmd), "sudo -u %s cat %s && echo 'Read OK' || echo 'Read Failed'", u, f);
	system(cmd);

	//Check write
	printf("Testing write for %s:\n", u);
	snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c 'echo x >> %s' 2>/dev/null && echo 'Write OK' || echo 'Write Failed'", u, f);
	system(cmd);
	return 0;
}
