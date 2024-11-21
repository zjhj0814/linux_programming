#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	pid_t pid;
	if(argc<2){
		printf("Usage: %s <prog> [prog_arg]\n",argv[0]);
		return 0;
	}
	pid = fork();
	if(pid==0){
		execvp(argv[1], &argv[1]);
		perror("execv failed\n");
	}
	else if(pid<0) perror("fork failed\n");
	else pid = wait(NULL);
	return 0;
}
