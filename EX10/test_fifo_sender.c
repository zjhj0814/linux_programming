#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 64

int main(int argc, char* argv[]){
	char buf[BUFSIZE];
	int fd;
	if(argc<3){
		printf("Usage: %s <fifo name> <message>", argv[0]); return 0;
	}
	if((fd=open(argv[1], O_WRONLY|O_NONBLOCK))<0){
		perror("open");
		return 0;
	}
	for(int i=2;i<argc;i++){
		if(strlen(argv[i])>BUFSIZE){
			printf("message too long %s\n", argv[i]);
			continue;
		}
		if(write(fd, argv[i], BUFSIZE)==-1){
			perror("sender write");
			return 0;
		}
	}
	return 0;
}
