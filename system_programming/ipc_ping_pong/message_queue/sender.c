/* C Program for Message Queue (Writer Process) */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main()
{
    key_t key;
    int msgid;
    char mesg_text[] = "ping - pong";
    size_t i = 0;

    /* ftok to generate unique key */
    key = ftok("/home/daniel/git/system_programming/ipc_ping_pong/message_queue/mq", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    for (i = 0; i < 3; ++i)
    {
        /* msgsnd to send message */
        msgsnd(msgid, &mesg_text, sizeof(mesg_text) + 1, 0);
    }

    /* display the message */
    printf("Data send is : %s \n", mesg_text);

    return 0;
}