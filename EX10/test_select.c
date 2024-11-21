#include <sys/select.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 64

void parent(int p[3][2]){
	char buf_char;
	char buf[BUFSIZE];
	int nread;
	fd_set readset, tempset;
	FD_ZERO(&readset);
	FD_SET(0, &readset);
	for(int i=0;i<3;i++){
		close(p[i][1]);
		FD_SET(p[i][0], &readset);
	}
	while(tempset=readset, select(p[2][0]+1, &tempset, NULL, NULL, NULL)>0){
		if(FD_ISSET(0,&tempset)){
			printf("Standard input: ");
			read(0, &buf_char, 1);
			printf("%c\n", buf_char);
		}
		for(int i=0;i<3;i++){
			if(FD_ISSET(p[i][0], &tempset)){
				if((nread = read(p[i][0], buf, BUFSIZE))>0){
					buf[nread] = '\0';
					printf("From child %d: %s\n", i, buf);
				}
			}
		}
	}
	if(waitpid(-1,NULL,WNOHANG)==-1) return ;
}

void child(int p[2]){
	close(p[0]);
	int num_repeat = getpid()%5;
	printf("Child %d will send message %d times\n", getpid(), num_repeat);
	for(int count = 0; count<getpid()%5; count++){
		write(p[1], "Hello", BUFSIZE);
		sleep(3);
	}
	return ;
}

int main(){
	int p[3][2];
	for(int i=0;i<3;i++){
		if(pipe(p[i])==-1){
			perror("pipe");
			return 0;
		}
		switch(fork()){
			case -1:
				perror("fork");
				return 0;
			case 0:
				child(p[i]);
				return 0;
		}
	}
	parent(p);
	while(wait(NULL)){}
	return 0;
}


