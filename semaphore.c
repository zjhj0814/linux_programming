#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define SEMPERM 0600
#define TRUE 1
#define FALSE 0

union semun{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
};

int initsem(key_t semkey){
	int status = 0, semid;

	if((semid = semget(semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL))==-1){
			if(errno == EEXIST) semid = semget(semkey, 1, 0);
	}
	else{
		union semun arg;
		arg.val = 1;
		status = semctl(semid, 0, SETVAL, arg);
	}
	if(semid == -1 || status == -1){
		perror("initsem failed");
		return -1;
	}
	return semid;
}

int p(int semid){ //wait, lock
	struct sembuf p_buf;

	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = SEM_UNDO;

	if(semop(semid, &p_buf, 1)==-1){
		perror("p(semid) failed");
		exit(1);
	}

	return 0;
}

int v(int semid){ //siganl, unlock
	struct sembuf v_buf;

	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = SEM_UNDO;

	if(semop(semid, &v_buf, 1)==-1){
		perror("v(semid) failed");
		exit(1);
	}
	return 0;
}

void handlesem(key_t skey){
	int semid;
	pid_t pid = getpid();
	if((semid = initsem(skey))<0) exit(1);
	
	printf("\nprocess %d before critical section\n", pid);
	p(semid);
	printf("process %d in critical section\n", pid);

	sleep(10); /* do something interesting */

	printf("process %d leaving critical section\n", pid);
	v(semid);
	printf("process %d exiting\n", pid);

	exit(0);
}

main(){
	key_t semkey = 0x200;
	for(int i=0;i<3;i++){
		if(fork()==0) handlesem(semkey);
	}
}
