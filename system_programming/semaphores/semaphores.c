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

#include "semaphores.h"

enum Status
{
    FAIL = -1
};

union semun
{
    int val;
    struct semid_ds *buf;
};

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
