#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define NAMELENGTH 11
#define NROOMS 10

char namebuf[NAMELENGTH];
int infile = -1;
char *getoccupier(int);
int main(int argc, char *argv[]){
	char* p;
	if(argc<2){
		printf("Usage : test_hotel <roomno a>, <roomno b>, ...\n");
		return -1;
	}
	for(int i=1;i<argc;i++){
		int roomno = atoi(argv[i]);
		if(p=getoccupier(roomno)) printf("Room %2d, %s\n", roomno, p);
		else printf("Error on room %d\n", roomno);
	}
	return 0;
}

char* getoccupier(int roomno){
	off_t offset;
	ssize_t nread;

	if(infile == -1 && (infile = open("residents", O_RDONLY)) ==-1){
		printf("Open file failed\n");
		return(NULL);
	}
	offset = (roomno-1)*NAMELENGTH;
	if(lseek(infile, offset, SEEK_SET)==-1){
		printf("lseek failed\n");
		return(NULL);
	}
	if((nread=read(infile, namebuf, NAMELENGTH))<=0){
		printf("Read failed\n");
		return (NULL);
	}
	namebuf[nread-1]='\0';
	return namebuf;
}
