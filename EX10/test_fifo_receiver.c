#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 64

int main(int argc, char* argv[]){
	char buf[BUFSIZE];
	int fd;
	if(argc!=2){
		printf("Usage: %s <fifo name>", argv[0]);
		return 0;
	}
	if(mkfifo(argv[1], 0666)==-1){
		if(errno!=EEXIST){
			perror("mkfifo");
			return 0;
		}
	}
	if((fd=open(argv[1], O_RDWR))<0){
		perror("open");
		return 0;
	}
	while(read(fd, buf, BUFSIZE)>0)
		printf("message received: %s\n", buf);
	return 0;
}
