#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0644
#define BUFSIZE 512

int copyfile(const char*, const char*);

int main(int argc, char* argv[]){
	char* infile = argv[1];
	char* outfile = argv[2];
	int retcode = copyfile(infile, outfile);
	if(retcode==0) printf("copy succeed!\n");
	else printf("copy failed with return code %d\n",retcode);
	return 0;
}

int copyfile(const char* name1, const char* name2){
	int infile, outfile;
	ssize_t nread;
	char buffer[BUFSIZE];
	if((infile = open(name1, O_RDONLY))==-1) return -1;
	if((outfile = open(name2, O_WRONLY|O_CREAT|O_EXCL, PERMS))==-1){
		close(infile);
		return -2;
	}
	while((nread = read(infile, buffer, BUFSIZE))>0){
		if(write(outfile,buffer,nread)<nread){
			close(infile);
			close(outfile);
			return -3;
		}
	}
	close(infile);
	close(outfile);
	if(nread==-1) return -4;
	else return 0;
}
