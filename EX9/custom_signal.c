#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sig_handler(int signo, siginfo_t* info, void* context){
	printf("\n[pid:%d] receive a signal(signo=%d) from %d process\n", getpid(), signo, info->si_pid);
	//kill(info->si_pid, signo);
}
		
int main(){
	pid_t pid;
	struct sigaction act;
        sigfillset(&act.sa_mask);
        act.sa_handler = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);

	if((pid = fork())==-1){
		perror("fork error");
		return 1;
	}
	
	if(pid == 0){
		for(int i=0;i<10;i++){
			sleep(1);
			kill(getppid(), SIGUSR1);
			printf("\n[%d] child send signal\n", i);
			pause();
		}
	}
	else{
		for(int i=0;i<10;i++){
			pause();
			sleep(1);
			kill(pid, SIGUSR1);
			printf("\n[%d] parent send signal\n", i);
		}
	}
	return 0;
}
