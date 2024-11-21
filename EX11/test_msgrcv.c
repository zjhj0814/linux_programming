#include "test_msg_header.h"

int msgid;

void sigint_handler(int sig) {
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}

int main() {
    key_t key;
    struct msg_entry msg;
    int msglen;

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sigint_handler;
    sigaction(SIGINT, &act, NULL);

    key = ftok("test_msg_header.h", 1);
    msgid = msgget(key, IPC_CREAT | QPERM);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while ((msglen = msgrcv(msgid, &msg, MAXLEN, 0, 0)) > 0) {
        printf("Received Message = %s\n", msg.mtext);
    }

    return 0;
}
