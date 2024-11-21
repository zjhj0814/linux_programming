#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void fpe_handler(int a){
	printf("\nSIGFPE caught\n");
	exit(1);
}

int main(){
	int error;
	struct sigaction act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = fpe_handler;

	sigaction(SIGFPE, &act, NULL);
	printf("fpe_handler() for SIGFPE is registered\n");

	error = 10/0;
	return 0;
}
