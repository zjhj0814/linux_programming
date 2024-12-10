#include <signal.h>
#include <stdlib.h>

void catchint(int);

void main(){
	static struct sigaction act;

	act.sa_handler = catchint;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	printf("sleep call #1\n");
	sleep(1);
	printf("sleep call #2\n");
	sleep(1);
	printf("sleep call #3\n");
	sleep(1);
	printf("sleep call #4\n");
	sleep(1);

	printf("Exiting\n");
	exit(0);
}

void catchint(int signo){
	printf("\nCATCHINT: signo=%d\n", signo);
	printf("CATCHINT: returning\n\n");
}
