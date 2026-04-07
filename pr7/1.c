#include <stdio.h>
#include <stdlib.h>

int main() {
	char buff[1024];
	//Opening ps aux for reading
	FILE *fp = popen("ps aux", "r");
	//Opening more for writing to show output page by page
	FILE *more = popen("more", "w");
	if (!fp || !more) return 1;
	//Reading from ps and pushing to more
	while (fgets(buff, sizeof(buff), fp)) fputs(buff, more);
	pclose(fp);
	pclose(more);
	return 0;
}
