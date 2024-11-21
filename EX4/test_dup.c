#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int fd;

	if(argc!=2){
		printf("Usage: test_dup <filename>\n");
		return -1;
	}
	fd = open(argv[1], O_WRONLY|O_CREAT,0644);
	if(fd==-1){
		printf("Opening %s failed\n",argv[1]);
		return -2;
	}
	else{
		printf("Before dup2()\n");
		dup2(fd,1);
		printf("After dup2()\n");
	}
	close(fd);
	return 0;
}
