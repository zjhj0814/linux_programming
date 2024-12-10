#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define TIMEOUT 5
#define MAXTRIES 5
#define LINESIZE 100
#define CTRL_G '\007'
#define TRUE 1
#define FALSE 0

static int timed_out;

static char answer[LINESIZE];

char* quickreply(char* prompt){
	void catch(int);
	int ntries;
	static struct sigaction act, oact;

	act.sa_handler = catch;
	sigaction(SIGALRM, &act, &oact);

	for(ntries = 0; ntries<MAXTRIES; ntries++){
		timed_out = FALSE;
		printf("\n%s > ", prompt);
		alarm(TIMEOUT);
		fgets(answer, LINESIZE, stdin);
		alarm(0);
		if(!timed_out){
			printf("timed_out is false!\n\n");
			break;
		}
	}
	sigaction(SIGALRM, &oact, NULL);
	return (ntries == MAXTRIES? ((char*)0) : answer);
}

void catch(int sig){
	timed_out = TRUE;
	putchar(CTRL_G); //Beep Sound!
}
