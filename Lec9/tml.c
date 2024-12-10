#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define BELLS '\007\007\007'

int alarm_flag = FALSE;

void setflag(int sig){
	printf("%d signal received!\n",sig);
	alarm_flag = TRUE;
}

void main(int argc, char** argv){
	int nsec, j, status;
	pid_t pid;

	static struct sigaction act;

	if(argc<2){
		fprintf(stderr, "Usage: tml #minutes message\n");
		exit(1);
	}

	if((nsec=atoi(argv[1])*60)<=0){
		fprintf(stderr, "tml: invalid time\n");
		exit(2);
	}

	switch(pid=fork()){
		case -1:
			perror("tml");
			exit(1);
		case 0 :
			break;
		default:
			printf("tml process - id %d\n",pid);
			wait(&status);
			printf("child process exit %d\n",status);
			exit(0);
	}

	act.sa_handler = setflag;
	sigaction(SIGALRM, &act, NULL);
	alarm(nsec);
	pause();

	if(alarm_flag == TRUE){
		printf("bells");
		for(j=2;j<argc;j++)
			printf("%s", argv[j]);
		printf("\n");
	}
	else printf("alarm_flag is false\n");

	exit(0);
}
