#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int msgid;
    int ret;

    key_t key = ftok("progfile", 43);

    msgid = msgget((key), IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("Message queue creation failed!\n");
        exit(1);
    }
    printf("Message queue is created with msgid = %d\n", msgid);

    struct mmsgbuf
    {
        long mtype;
        char mtext[100];
    } message;

    // message.mtype = 1;
    // strcpy(message.mtext, "Hello person !");

    ret = msgrcv(msgid, &message, sizeof(message), 1, 0);

    if (ret == -1)
    {
        perror("Failed to receive message!\n");
        exit(1);
    }

    printf("Message received!\n");
    printf("The Message is: %s\n", message.mtext);
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}