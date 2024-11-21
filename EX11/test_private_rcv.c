#include "test_msg_header.h"

int main() {
    key_t key;
    int msgid;
    struct msg_entry msg;
    int msglen;

    key = ftok("test_msg_header.h", 1);
    msgid = msgget(key, IPC_CREAT | QPERM);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while ((msglen = msgrcv(msgid, &msg, MAXLEN, -10, 0)) > 0) {
        printf("Received Message = %s\n", msg.mtext);
    }

    return 0;
}
