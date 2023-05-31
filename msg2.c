#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>

int main()
{
    int msgid;

    key_t key = ftok("progfile", 90);

    msgid = msgget((key), IPC_CREAT | IPC_EXCL);

    if (msgid == -1)
    {
        perror("Message queue creation failed!");
        exit(1);
    }

    printf("Message queue is created with msgid = %d\n", msgid);

    return 0;
}