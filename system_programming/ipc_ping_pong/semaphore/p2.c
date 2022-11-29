/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Stav
Date: 16/06/2022
File: Semaphore
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <sys/types.h> /* ftok, semget */
#include <sys/ipc.h>   /* ftok, semget */
#include <sys/sem.h>   /* semget */
#include <string.h>    /* memset */
#include <stdio.h>     /* printf */
#include <unistd.h>    /* sleep */

enum Status
{
    FAIL = -1
};

union semun
{
    int val;
    struct semid_ds *buf;
};

int SemCreate(char *file_path, char id, size_t start_value);
int SemDestroy(int sem_id);
int SemIncrease(int id, int num, int set_undo);
int SemDecrease(int id, int num, int set_undo);

int main()
{
    int sem_id1 = SemCreate("/", 'a', 0);
    int sem_id2 = SemCreate("/", 'b', 0);
    size_t i = 0;

    printf("1: %d\n", sem_id1);
    printf("2: %d\n", sem_id2);

    for (i = 0; i < 10; ++i)
    {

        SemDecrease(sem_id1, 1, 0);
        sleep(1);
        printf("pong\n");

        SemIncrease(sem_id2, 1, 0);
    }

    SemDestroy(sem_id2);

    return 0;
}

int SemCreate(char *file_path, char id, size_t start_value)
{
    key_t key = {0};
    int sem_id = 0;

    key = ftok(file_path, id);
    sem_id = semget(key, 1, IPC_CREAT | 0666);

    if (FAIL == sem_id)
    {
        return FAIL;
    }

    if (FAIL == semctl(sem_id, 0, SETVAL, start_value))
    {
        SemDestroy(sem_id);
        return FAIL;
    }

    return sem_id;
}

int SemDestroy(int sem_id)
{
    return semctl(sem_id, 0, IPC_RMID);
}

int SemIncrease(int id, int num, int set_undo)
{
    struct sembuf signal = {0, 0, 0};

    signal.sem_op = num;
    if (1 == set_undo)
    {
        signal.sem_flg = SEM_UNDO;
    }

    return semop(id, &signal, 1);
}

int SemDecrease(int id, int num, int set_undo)
{
    struct sembuf wait = {0, 0, 0};

    wait.sem_op = -num;
    if (1 == set_undo)
    {
        wait.sem_flg = SEM_UNDO;
    }

    return semop(id, &wait, 1);
}

int SemView(int sem_id)
{
    return semctl(sem_id, 0, GETVAL);
}
