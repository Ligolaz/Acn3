#include <stdio.h>
#include <stdlib.h>

void check(const char *u, const char *p) {
	printf("\nChecking: %s\n", p);
	char cmd[512];
	//Using shell test flags -r -w -x
	snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c '[ -r %s ] && echo \"+R\" || echo \"-R\"; [ -w %s ] && echo \"+W\" || echo \"-W\"; [ -x %s ] && echo \"+X\" || echo \"-X\"'", u, p, p, p);
	system(cmd);
}

int main() {
	const char *u = "user";
	printf("---Home Dir---\n");
	system("ls -l ~ | head -n 5");
	printf("\n---/etc Dir---\n");
	system("ls -l /etc | head -n 5");

	check(u, "/etc/shadow");
	check(u, "/etc/passwd");
	check(u, "/usr/bin/ls");
	return 0;
}
