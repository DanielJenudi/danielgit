/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Stav
Date: 16/06/2022
File: Semaphore
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi */

#include "semaphores.h"

enum Status
{
    FAIL = -1,
    SUCCESS = 0
};

enum End_Commend
{
    FAIL_COMMAND = -1,
    CONTINUE = 0,
    RETURN = 1,
    EXIT = 2
};

enum Undo
{
    UNDO_OFF = 0,
    UNDO_ON = 1
};

static void StartManual(void);
static void OperationManual(int sem_id);

static void StartProgram(void);
static int CreatNewSem(char *command);
static int DeleteSem(char *num);
static int ViweAllSem();

static int SelectOpSem(char *num);
static int AddSem(int sem_id, char *num);
static int SubtractSem(int sem_id, char *num);
static int ViewSem(int sem_id);

int main()
{
    StartProgram();

    return 0;
}

static void StartProgram(void)
{
    int flag = CONTINUE;
    char command[100] = {0};

    StartManual();

    while (CONTINUE == flag)
    {
        scanf("%[^\n]%*c", command);

        switch (*command)
        {
        case 'C':
            flag = CreatNewSem(&command[2]);
            break;

        case 'D':
            flag = DeleteSem(&command[2]);
            break;

        case 'O':
            flag = SelectOpSem(&command[2]);
            break;

        case 'A':
            flag = ViweAllSem();
            break;

        case 'X':
            printf("Goodbay!\n");
            flag = EXIT;
            break;

        default:
            printf("\nUnvaild command\n");
            StartManual();
            break;
        }
    }
}

static int CreatNewSem(char *command)
{
    int sem_id = 0;
    char *key = NULL;
    char *file_path = NULL;

    key = command;
    file_path = command + 2;

    sem_id = SemCreate(file_path, *key, 0);

    if (FAIL == sem_id)
    {
        printf("Fail to creat new Semaphore\n");
        return FAIL_COMMAND;
    }
    else
    {
        printf("New Semaphore id: %d \n\n", sem_id);
        return CONTINUE;
    }
}

static int DeleteSem(char *num)
{
    int sem_id = 0;
    sem_id = atoi(num);

    if (FAIL == SemDestroy(sem_id))
    {
        printf("Fail to delete Semaphore\n");
        return FAIL_COMMAND;
    }
    else
    {
        printf("Semaphore %d delete succesfuly\n\n", sem_id);
        return CONTINUE;
    }
}

static int ViweAllSem()
{
    if (FAIL == system("ipcs -s"))
    {
        printf("System Fail\n");
        return FAIL_COMMAND;
    }
    else
    {
        return CONTINUE;
    }
}

static int SelectOpSem(char *num)
{
    int sem_id = 0;
    int flag = CONTINUE;
    char command[100] = {0};
    sem_id = atoi(num);

    OperationManual(sem_id);

    while (CONTINUE == flag)
    {
        scanf("%[^\n]%*c", command);

        switch (*command)
        {
        case 'I':
            flag = AddSem(sem_id, &command[2]);
            break;

        case 'D':
            flag = SubtractSem(sem_id, &command[2]);
            break;

        case 'V':
            flag = ViewSem(sem_id);
            break;

        case 'R':
            flag = RETURN;
            break;

        case 'X':
            flag = EXIT;
            break;

        default:
            printf("\nUnvaild command\n");
            OperationManual(sem_id);
            break;
        }
    }

    if (flag == EXIT)
    {
        printf("Goodbay!\n");
        return EXIT;
    }

    if (flag == RETURN)
    {
        StartManual();
        return CONTINUE;
    }

    return FAIL_COMMAND;
}

static int AddSem(int sem_id, char *command)
{
    int num_to_increase = 0;
    int undo_flag = UNDO_OFF;

    if ('U' == *command)
    {
        undo_flag = UNDO_ON;
        command += 2;
    }

    num_to_increase = atoi(command);

    if (FAIL == SemIncrease(sem_id, num_to_increase, undo_flag))
    {
        printf("Increase Fail\n");
        return FAIL_COMMAND;
    }

    printf("Increase Succsess\n\n");
    return CONTINUE;
}

static int SubtractSem(int sem_id, char *command)
{
    int num_to_decrease = 0;
    int undo_flag = UNDO_OFF;

    if ('U' == *command)
    {
        undo_flag = UNDO_ON;
        command += 2;
    }

    num_to_decrease = atoi(command);

    if (FAIL == SemDecrease(sem_id, num_to_decrease, undo_flag))
    {
        printf("Decrease Fail\n");
        return FAIL_COMMAND;
    }

    printf("Decrease Succsess\n\n");
    return CONTINUE;
}

static int ViewSem(int sem_id)
{
    int cur = SemView(sem_id);
    if (FAIL == cur)
    {
        printf("View Fail\n");
        return FAIL_COMMAND;
    }

    printf("Value of Semaphore is: %d\n\n", cur);
    return CONTINUE;
}

static void StartManual(void)
{
    printf("\nSemphore manipulation program:\n"
           "\nChosse operation:\n"
           "C <Key> <File Path> - Create Semaphore\n"
           "D <Sem ID> - Delete Semaphore\n"
           "O <Sem ID> - Open opeation manual for Semaphre\n"
           "A - View all Semaphores in the system\n"
           "X - Exit program\n\n");
}

static void OperationManual(int sem_id)
{
    printf("\nOperation Manual for Semaphore ID: %d\n", sem_id);
    printf("\nChosse operation:\n"
           "I (Potential: <U>) <Number> - Increase Semaphore value, U - undo\n"
           "D (Potential: <U>) <Number> - Decrease Semaphore value, U - undo\n"
           "V - View Semaphore value\n"
           "R - Return to main page\n"
           "X - Exit program\n\n");
}