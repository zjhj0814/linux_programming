#include <signal.h>

void sig_handler(int signo, siginfo_t* siginfo, void* param2){
	printf("[Parent:%d]: receive a signal from child %d\n",getpid(), siginfo->si_pid);
}

int main(){
	pid_t pid;
	static struct sigaction act;
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigfillset(&act.sa_mask);
	sigaction(SIGUSR1, &act, 0);

	int i = 0;
	while(pid=fork()){
		printf("[Parent: %d]: create child %\n\n",getpid(), pid);
		if(i++==3) break;
	}
	if(pid>0){
		getchar();
	}
	else{
		kill(getppid(), SIGUSR1);
	}
	return 0;
}
