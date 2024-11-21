#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
	switch(fork()){
		case -1:
			perror("fork");
			return 1;
		case 0:
			sleep(2);
			kill(getppid(), SIGKILL);
			printf("[pid:%d] I killed my parent\n", getpid());
			return 0;
		default:
			printf("[pid:%d] I'm going to sleep\n", getpid());
			sleep(10);
			printf("[pid:%d] I wake up\n",getpid());
			return 0;
	}
}
