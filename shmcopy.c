#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHMKEY1 (key_t) 0x10
#define SHMKEY2 (key_t) 0x15
#define SHMKEY3 (key_t) 0x20

#define SIZ 5*BUFSIZE

#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct databuf*)-1)

struct databuf{
	int d_nread;
	char d_buf[SIZ];
};

typedef union _semun{
	int val;
	struct semid_ds* buf;
	ushort* array;
} semun;

static int shmid1, shmid2, semid;

void getseg(struct databuf** p1, struct databuf** p2){
	if((shmid1=shmget(SHMKEY1, sizeof(struct databuf), 0600|IFLAGS))==-1) fatal("shmget");
	if((shmid2=shmget(SHMKEY2, sizeof(struct databuf), 0600|IFLAGS))==-1) fatal("shmget");

	if((*p1=(struct databuf*) shmat(shmid1,0,0))==ERR) fatal("shmat");
	if((*p2=(struct databuf*) shmat(shmid2,0,0))==ERR) fatal("shmat");
}

int getsem(void){
	semun x;
	x.val = 0;

	if((semid = semget(SEMKEY, 2, 0600 | IFLAGS))==-1) fatal("semget");

	if(semctl(semid, 0, SETVAL, x)==-1) fatal("semctl");
	if(semctl(semid, 1, SETVAL, x)==-1) fatal("semctl");
	return semid;
}

void remobj(void){
	if(shmctl(shmid1, IPC_RMID, NULL) ==-1) fatal("shmctl");
	if(shmctl(shmid2, IPC_RMID, NULL) ==-1) fatal("shmctl");
	if(shmctl(semid, IPC_RMID, NULL)==-1) fatal("semctl");
}

void reader(int semid, struct databuf* buf1, struct databuf* buf2){
	for(;;){
		buf1->d_nread = read(0,buf1->d_buf, SIZ);
		semop(semid, &v1, 1);
	}
}

