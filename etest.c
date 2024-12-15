#include <stdlib.h>
#include "q.h"

main(int argc, char** argv){
	int priority;

	if(argc!=3){
		fprintf(stderr, "usage: %s objname priority\n", argv[0]);
		exit(1);
	}

	if((priority = atoi(argv[2])) <= 0 || priority > MAXPRIOR){
		warn("invalid priority");
		exit(2);
	}

	if(enter(argv[1], priority)<0){
		warn("enter failure");
		exit(3);
	}
	exit(0);
}
