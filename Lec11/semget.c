#include <errno.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

void main(int argc, char** argv){
	key_t skey;
	int semid;

	if(argc!=3){
		fprintf(stderr, "Usage: %s pathname id\n", argv[0]);
		exit(1);
	}

	if((skey = ftok(argv[1], atoi(argv[2])))==(key_t)-1){
		fprintf(stderr, "failed to derive key from filename %s\n", argv[1]);
		exit(1);
	}
	if((semid = semget(skey, 2, 0660 | IPC_CREAT))==-1){
		fprintf(stderr, "failed to create semaphore with key %d\n", (int) skey);
		exit(1);
	}
	printf("semid = %d\n", semid);
	return 0;
}

