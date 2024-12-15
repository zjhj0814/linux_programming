#include <stdlib.h>
#include "q.h"

main(){
	pid_t pid;

	switch(pid=fork()){
		case -1:
			warn("fork to start server failed");
			exit(1);
		case 0:
			serve();
			break;
		default:
			printf("server process pid is %d\n", pid);
	}
	exit(0);
}
