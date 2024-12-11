#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define MSGSIZE 63

char* fifo = "fifo";

void fatal(char* s){
	perror(s);
	exit(1);
}

void main(int argc, char** argv){
	int fd, nwrite;
	char msgbuf[MSGSIZE+1];
	if(argc<2){
		fprintf(stderr, "Usage: sendmessage msg...\n");
		exit(1);
	}
	if((fd=open(fifo, O_WRONLY|O_NONBLOCK))<0){
		fatal("fifo open failed");
	}
	for(int i=1;i<argc;i++){
		if(strlen(argv[i])>MSGSIZE){
			fprintf(stderr, "message too long %s\n",argv[i]);
			continue;
		}
		strcpy(msgbuf, argv[i]);
		if((nwrite = write(fd, msgbuf, MSGSIZE+1))==-1) fatal("message write failed");
	}
	exit(0);
}
