#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define QKEY (key_t) 0105
#define QPERM 0660
#define MAXOBN 50
#define MAXPRIOR 10

struct q_entry{
	long mtype;
	char mtext[MAXOBN+1];
};

void warn(char* s){
	fprintf(stderr,"warning: %s\n",s);
}

int init_queue(void){
	int queue_id;

	if((queue_id=msgget(QKEY, IPC_CREAT|QPERM))==-1) perror("msgget failed");
	return queue_id;
}

int enter(char* objname, int priority){
	int len, s_qid;
	struct q_entry s_entry;

	if((len = strlen(objname))>MAXOBN){
		warn("name too long");
		return -1;
	}
	if(priority>MAXPRIOR||priority<0){
		warn("invalid priority level");
		return -1;
	}
	if((s_qid = init_queue())==-1) return -1;
	s_entry.mtype = (long) priority;
	strncpy(s_entry.mtext, objname, MAXOBN);

	if(msgsnd(s_qid, &s_entry, len,0)==-1){
		perror("msgsnd failed");
		return -1;
	}
	return 0;
}

int serve(void){
	int mlen, r_qid;
	struct q_entry r_entry;

	if((r_qid=init_queue())==-1) return -1;
	for(;;){
		if((mlen = msgrcv(r_qid, &r_entry, MAXOBN, (-1*MAXPRIOR), MSG_NOERROR))==-1){
			perror("msgrcv failed");
			return -1;
		}
		else{
			r_entry.mtext[mlen]='\0';
			printf("\npriority: %ld name: %s\n", r_entry.mtype, r_entry.mtext);
		}
	}
}
