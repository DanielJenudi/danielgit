#include <string.h>    /* strcmp */
#include <stdlib.h>    /* system */
#include <stdio.h>     /* printf */
#include <unistd.h>    /* fork, execl */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait */
#include <assert.h>    /* assert */
#include <ctype.h>     /* isspace */

#include "simpleshell.h"

#define COMAND_MAX_LEN (100)
#define COMAND_MAX_NUM_OF_VAR (100)
#define WAIT_FAIL (-1)
#define FORK_FAIL (-1)
#define SYSTEM_FAIL (-1)
#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

static int SimpleShellFork(void);
static int SimpleShellSystem(void);
static void ModifyCommand(char *command, char **comand_arr);
static char *SkipWhitSpace(char *runner);

enum Status
{
    SUCCESS = 0,
    FAIL = 1,
    TRUE = 1,
    FALSE = 0
};

int SimpleShell(const char *fork_or_system)
{
    assert(NULL != fork_or_system);

    if (SUCCESS == strcmp(fork_or_system, "fork"))
    {
        return SimpleShellFork();
    }
    else if (SUCCESS == strcmp(fork_or_system, "system"))
    {
        return SimpleShellSystem();
    }

    return FAIL;
}

static int SimpleShellFork(void)
{
    pid_t child_pid = 0;
    char *comand = NULL;
    char **comand_arr = NULL;

    comand = (char *)malloc(COMAND_MAX_LEN * sizeof(char));
    if (NULL == comand)
    {
        return FAIL;
    }

    comand_arr = (char **)malloc(COMAND_MAX_NUM_OF_VAR * sizeof(char *));
    if (NULL == comand_arr)
    {
        FREE(comand);
        return FAIL;
    }

    scanf("%[^\n]%*c", comand);
    while (SUCCESS != strcmp(comand, "exit"))
    {
        child_pid = fork();
        if (FORK_FAIL == child_pid)
        {
            return FAIL;
        }

        if (0 == child_pid)
        {
            ModifyCommand(comand, comand_arr);
            return !!execvp(*comand_arr, comand_arr);
        }

        if (WAIT_FAIL == wait(NULL))
        {
            return FAIL;
        }

        scanf("%[^\n]%*c", comand);
    }

    FREE(comand);
    FREE(comand_arr);

    return SUCCESS;
}

static void ModifyCommand(char *command, char **comand_arr)
{
    char *str_start = NULL;
    char *runner = NULL;

    assert(NULL != command);
    assert(NULL != comand_arr);

    runner = SkipWhitSpace(command);
    str_start = runner;

    while ('\0' != *runner)
    {
        if (FALSE != isspace(*runner))
        {
            /*set in comand_arr pointer to current word*/
            *comand_arr = str_start;
            ++comand_arr;

            /*move runner to next not space char, and str_start to next word */
            runner = SkipWhitSpace(runner);
            str_start = runner;
        }
        ++runner;
    }

    if ('\0' != *str_start)
    {
        *comand_arr = str_start;
        ++comand_arr;
    }

    *comand_arr = NULL;
}

static char *SkipWhitSpace(char *runner)
{
    assert(NULL != runner);

    while (FALSE != isspace(*runner))
    {
        *runner = '\0';
        ++runner;
    }

    return runner;
}

static int SimpleShellSystem(void)
{
    char *comand = (char *)malloc(COMAND_MAX_LEN * sizeof(char));
    if (NULL == comand)
    {
        return FAIL;
    }

    scanf("%[^\n]%*c", comand);
    while (SUCCESS != strcmp(comand, "exit"))
    {
        if (SYSTEM_FAIL == system(comand))
        {
            return FAIL;
        }
        scanf("%[^\n]%*c", comand);
    }

    FREE(comand);

    return SUCCESS;
}