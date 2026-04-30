#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test_fs(const char *path, const char *fs_name) {
	printf("\n---Testing FS: %s---\n", fs_name);
	char target[256];
	snprintf(target, sizeof(target), "%s/weird_file", path);

	//Creating file with owner-execute-only perms (non-standard)
	char cmd[1024];
	snprintf(cmd, sizeof(cmd), "echo 'data' > %s && chmod 100 %s", target, target);
	if (system(cmd) != 0) {
		printf("Error: Cannot create file in %s\n", path);
		return;
	}

	//Trying to read a file that only has execute bits
	printf("Read attempt: ");
	snprintf(cmd, sizeof(cmd), "cat %s 2>/dev/null && echo 'OK' || echo 'Denied'", target);
	system(cmd);

	//Deleting file (perms of the file don't matter, only perms of the directory)
	if (unlink(target) == 0) printf("Deletion: Success (Dir perms allow this)\n");
}

int main() {
	//In ubuntu home is ext4, /tmp is tmpfs
	test_fs(".", "ext4");
	test_fs("/tmp", "tmpfs");

	//To test NFS I'd need an actual OS
	//But we're using ubuntu through virtual machine here
	//test_fs("/mnt/nfs", "NFS");
	return 0;
}
