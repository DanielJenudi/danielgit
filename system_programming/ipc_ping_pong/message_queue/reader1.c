
/* C Program for Message Queue (Reader Process) */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* structure for message queue */
struct mesg_buffer
{
    long mesg_type;

} message;

int main()
{
    key_t key;
    int msgid;
    char mesg_text[100];

    /* ftok to generate unique key */
    key = ftok("/home/daniel/git/system_programming/ipc_ping_pong/message_queue/mq", 65);

    /* msgget creates a message queue */
    /* and returns identifier */
    msgid = msgget(key, 0666 | IPC_CREAT);

    /* msgrcv to receive message */
    msgrcv(msgid, mesg_text, sizeof(mesg_text), 0, 0);

    /* display the message */
    printf("Data Received reader1 is : %s \n", mesg_text);

    return 0;
}