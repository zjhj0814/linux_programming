#include "test_msg_header.h"

int main() {
    key_t key;
    int msgid;
    struct msg_entry msg;

    key = ftok("test_msg_header.h", 1);
    msgid = msgget(key, IPC_CREAT | QPERM);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    for (int i = 10; i > 0; i--) {
        msg.mtype = i;
        char message[MAXLEN];
        sprintf(message, "message type %d\n", i);
        strcpy(msg.mtext, message);
        if (msgsnd(msgid, (void*)&msg, MAXLEN, IPC_NOWAIT) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
