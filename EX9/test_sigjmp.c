#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
sigjmp_buf position;

void int_handler(int a){
	printf("\nSIGINT caught\n");
	siglongjmp(position,1);
}

int main(){
	struct sigaction act;
	sigfillset(&act.sa_mask);
	act.sa_handler = int_handler;
	sigaction(SIGINT, &act, NULL);
	printf("int_handler() for SIGINT is registered\n");
	
	int temp = sigsetjmp(position, 1);
	printf("sigsetjmp returns %d\n",temp);
	for(int i=0;i<4;i++){
		printf("sleep call #%d\n",i);
		sleep(3);
	}
	return 0;
}
