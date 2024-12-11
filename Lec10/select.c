#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define MSGSIZE 6

char* msg1 = "hello";
char* msg2 = "bye!!";

void parent(int[3][2]);
int child(int[2]);
void fatal(char*s){
	perror(s);
	exit(1);
}

void main(){
	int pip[3][2];
	for(int i=0;i<3;i++){
		if(pipe(pip[i])==-1) fatal("pipe call");
		switch(fork()){
			case -1:
				fatal("fork call");
			case 0:
				child(pip[i]);
		}
	}
	parent(pip);
	exit(0);
}


void parent(int p[3][2]){
	char buf[MSGSIZE], ch;
	fd_set set, master;
	for(int i=0;i<3;i++) close(p[i][1]);
	FD_ZERO(&master);
	FD_SET(0, &master);
	for(int i=0;i<3;i++) FD_SET(3+2*i, &master);
	while(set=master, select(3+2*3+1, &set, NULL, NULL, NULL)>0){
		if(FD_ISSET(0, &set)){
			printf("From standard input ...");
			read(0,&ch,1);
			printf("%c\n",ch);
		}
		for(int i=0;i<3;i++){
			if(FD_ISSET(3+2*i, &set)){
				if(read(p[i][0],buf,MSGSIZE)>0){
					printf("Message from child %d\n",i);
					printf("MSG=%s\n",buf);
				}
			}
		}
		if(waitpid(-1,NULL,WNOHANG)==-1) return ;
	}
}

int child(int p[2]){
	close(p[0]);

	for(int count = 0; count<2; count++){
		write(p[1], msg1, MSGSIZE);
		sleep(getpid()%4);
	}
	write(p[1],msg2,MSGSIZE);
	exit(0);
}



