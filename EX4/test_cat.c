#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512

int main(int argc, char *argv[]){
	char *infile = argv[1];
	int filedes; 
	ssize_t nread;
	char buffer[BUFSIZE];

	if((filedes = open(filedes, O_RDONLY))==-1) return -1;
	while((nread = read(filedes, buffer, BUFSIZE))>0){
		if(write(1,buffer, nread)<nread){
			close(filedes);
			return -3;
		}
	}
	close(filedes);
	if(nread==-1) return -4;
	else return 0;
}
