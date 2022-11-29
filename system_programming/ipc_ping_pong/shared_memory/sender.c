#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    /* ftok to generate unique key */
    key_t key = ftok("shmfile", 65);

    /* shmget returns an identifier in shmid */
    int shmid = shmget(key, getpagesize(), 0666 | IPC_CREAT);

    /* shmat to attach to shared memory */
    char *str = (char *)shmat(shmid, (void *)0, 0);

    /* printf("page size: %d\n", getpagesize()); */

    memcpy(str, "ping - pong", sizeof("ping - pong") + 1);

    printf("Data written in memory: %s\n", str);

    /* detach from shared memory */
    shmdt(str);

    return 0;
}