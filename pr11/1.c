#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ucontext.h>
#include <unistd.h>
#include <string.h>

//Simple helper to write text to stderr without printf
void wr(const char *s) {
	write(STDERR_FILENO, s, strlen(s));
}

//Function to convert number to hex string and print it
void wr_hex(unsigned long long v) {
	char buf[19];
	char *hex = "0123456789abcdef";
	buf[0] = '0'; buf[1] = 'x';
	for(int i = 17; i >= 2; i--) {
		buf[i] = hex[v & 0xf];
		v >>= 4;
	}
	buf[18] = '\0';
	wr(buf);
}

//The crash handler
void crash_handler(int sig, siginfo_t *info, void *ctx) {
	ucontext_t *uc = (ucontext_t *)ctx;

	wr("\nCRASH LOG START.\n");
	wr("Signal received: ");
	if(sig == SIGSEGV) wr("SIGSEGV (Memory Corruption)\n");
	else wr("Fatal error\n");

	wr("Fault address: ");
	wr_hex((unsigned long long)info->si_addr);
	wr("\n\nREGISTER DUMP:\n");

#if defined(__x86_64__)
	//Specific registers for x86_64 architecture
	wr("RIP: "); wr_hex(uc->uc_mcontext.gregs[REG_RIP]); wr("\n");
	wr("RAX: "); wr_hex(uc->uc_mcontext.gregs[REG_RAX]); wr("\n");
	wr("RSP: "); wr_hex(uc->uc_mcontext.gregs[REG_RSP]); wr("\n");
	wr("RBP: "); wr_hex(uc->uc_mcontext.gregs[REG_RBP]); wr("\n");
#else
	//Generic message for other architectures
	wr("Register dump not implemented for this CPU arch.\n");
#endif

	wr("CRASH LOG END.\n");
	_exit(1);
}

int main() {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = crash_handler;
	//SA_SIGINFO is required to get the context
	sa.sa_flags = SA_SIGINFO;

	//Catching major crash signals
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);

	wr("App running. Triggering crash...\n");

	//Artificial segmentation fault
	int *ptr = NULL;
	*ptr = 1337;

	return 0;
}
