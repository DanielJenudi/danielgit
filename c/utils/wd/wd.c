/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 30/06/2022
File: WatchDog
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#define _DEFAULT_SOURCE 200112L /* env var */

#include <stdio.h>     /* printf */
#include <time.h>      /* time */
#include <unistd.h>    /* fork, execl */
#include <sys/types.h> /* pid_t */
#include <pthread.h>   /* pthread */
#include <stdatomic.h> /* atomic_int */
#include <signal.h>    /* SIGUSR1, SIGUSR2 */
#include <stdlib.h>    /* setenv, getenv */
#include <string.h>    /* strcmp */
#include <assert.h>    /* assert */

#include "uid.h"
#include "sched.h"
#include "wd.h"
#include "semaphores.h"

#define CHECK_PULSE_FREQUENCY (3)
#define SEND_SIGNAL_FREQUENCY (1)
#define STOP (0)
#define SIZEOF_OF_PID (15)
#define WD_PROGRAM_NAME ("./watchdog.out")
#define ENV_NAME ("WD_PID")
#define REMAIN_VAR (0)
#define CLIENT_DEAD (-1)

enum Status
{
    SUCCESS = 0,
    FAIL = -1,
    TRUE = 1,
    FALSE = 0
};

enum WhoAmI
{
    CLIENT = 0,
    WD
};

enum Pulse
{
    RESTART_COUNTER = 0,
    PULSE_LIMIT = 10
};

enum StopFlag
{
    INACTIVE = 0,
    ACTIVE
};

/* semaphores */
static int CreateSemaphores(void);
static void DestroySemaphores(void);
static void AllSetClientProgramRelease(void);
static void FailSetSem(void);
static int WaitforWDSetup(void);

static int SendSignalToTarget(void *param);
static void StopSched(void *param);
static void *StartSched(void *compile_str);
static int CreateWD(void *argv);
static int CreateSignalHandlers(void);
static int CreateClientThread(void *argv);
static void GetLifeSign(int signal);
static void ActiveStopFlag(int signal);
static int Identify(void);
static int CheckTargetPulse(void *argv);
static int RebootClient(void *argv);
static int RebootWD(void *argv);

static atomic_int g_is_target_alive = 0;
static pid_t g_target_pid = 0;
static int g_who_am_i = 0;
static int g_stop_flag = INACTIVE;

/* semaphores */
static int g_semid = 0;
static int g_thread_checker_semid = 0;
static int g_watchdog_checker_semid = 0;

int WDStart(const char *compile_str[])
{
    int status = SUCCESS;

    assert(NULL != compile_str);

    g_who_am_i = Identify();
    if (FAIL == g_who_am_i)
    {
        return FAIL;
    }

    status = CreateSignalHandlers();
    if (FAIL == status)
    {
        return FAIL;
    }

    status = CreateSemaphores();
    if (FAIL == status)
    {
        return FAIL;
    }

    if (CLIENT == g_who_am_i)
    {
        status += CreateClientThread((void *)compile_str);

        status += CreateWD(compile_str);
    }
    else
    {
        g_target_pid = getppid();

        status = SemIncrease(g_semid, 2, 0);
        if (SUCCESS != status)
        {
            DestroySemaphores();
            return FAIL;
        }

        StartSched((void *)compile_str);

        return SUCCESS;
    }

    if (SUCCESS != status)
    {
        DestroySemaphores();
        return FAIL;
    }

    return WaitforWDSetup();
}

static int CreateSemaphores(void)
{
    g_semid = SemCreate("./", 's', 0);
    if (FAIL == g_semid)
    {
        return FAIL;
    }

    g_watchdog_checker_semid = SemCreate("./", 't', 0);
    if (FAIL == g_semid)
    {
        DestroySemaphores();
        return FAIL;
    }

    if (CLIENT == g_who_am_i)
    {
        g_thread_checker_semid = SemCreate("./", 'w', 0);
        if (FAIL == g_semid)
        {
            DestroySemaphores();
            return FAIL;
        }
    }

    return SUCCESS;
}

static void DestroySemaphores(void)
{
    SemDestroy(g_semid);
    SemDestroy(g_thread_checker_semid);
    SemDestroy(g_watchdog_checker_semid);
}

static void AllSetClientProgramRelease(void)
{
    if (CLIENT == g_who_am_i)
    {
        SemIncrease(g_thread_checker_semid, 1, 0);
    }
    else
    {
        SemIncrease(g_watchdog_checker_semid, 1, 0);
    }
}

static void FailSetSem(void)
{
    if (CLIENT == g_who_am_i)
    {
        SemIncrease(g_thread_checker_semid, 2, 0);
    }
    else
    {
        SemIncrease(g_watchdog_checker_semid, 2, 0);
    }
}

static int WaitforWDSetup(void)
{
    SemDecrease(g_thread_checker_semid, 1, 0);
    SemDecrease(g_watchdog_checker_semid, 1, 0);

    if ((SUCCESS != SemView(g_thread_checker_semid)) ||
        (SUCCESS != SemView(g_thread_checker_semid)))
    {
        WDStop();
        DestroySemaphores();
        return FAIL;
    }

    DestroySemaphores();
    return SUCCESS;
}

static int CreateSignalHandlers(void)
{
    struct sigaction sig = {0};

    sig.sa_handler = &GetLifeSign;
    if (SUCCESS != sigaction(SIGUSR1, &sig, NULL))
    {
        return FAIL;
    }

    sig.sa_handler = &ActiveStopFlag;
    if (SUCCESS != sigaction(SIGUSR2, &sig, NULL))
    {
        return FAIL;
    }

    return SUCCESS;
}

static int CreateWD(void *argv)
{
    pid_t wd_pid = 0;

    wd_pid = fork();
    if (FAIL == wd_pid)
    {
        return FAIL;
    }

    if (0 == wd_pid)
    {
        return execvp(WD_PROGRAM_NAME, (char *const *)argv);
        printf("exec boot wd fail\n");
    }

    g_target_pid = wd_pid;

    return SUCCESS;
}

static int CreateClientThread(void *argv)
{
    pthread_t tid = 0;

    assert(NULL != argv);

    if (SUCCESS != pthread_create(&tid, NULL, &StartSched, argv))
    {
        printf("thread creat fail\n");
        return FAIL;
    }

    if (SUCCESS != pthread_detach(tid))
    {
        printf("thread detach fail\n");
        return FAIL;
    }

    return SUCCESS;
}

static void *StartSched(void *compile_str)
{
    sched_t *sched = NULL;
    ilrd_uid_t uid = UIDBadUID;
    sc_action_func_t check_opponent_pulse = &CheckTargetPulse;
    sc_action_func_t send_sig = &SendSignalToTarget;
    sc_clean_up_func_t stop_func = &StopSched;

    assert(NULL != compile_str);

    sched = SchedCreate();
    if (NULL == sched)
    {
        FailSetSem();
        return NULL;
    }

    uid = SchedAddTask(sched, send_sig, NULL, stop_func,
                       (void *)sched, time(NULL) + SEND_SIGNAL_FREQUENCY);
    if (TRUE == UIDIsSame(uid, UIDBadUID))
    {
        FailSetSem();
        return NULL;
    }

    uid = SchedAddTask(sched, check_opponent_pulse, compile_str, stop_func,
                       (void *)sched, time(NULL) + CHECK_PULSE_FREQUENCY);
    if (TRUE == UIDIsSame(uid, UIDBadUID))
    {
        FailSetSem();
        return NULL;
    }

    SemDecrease(g_semid, 1, 0);

    AllSetClientProgramRelease();
    SchedRun(sched);

    DestroySemaphores();
    SchedDestroy(sched);
    sched = NULL;

    if (CLIENT_DEAD == g_is_target_alive)
    {
        RebootClient(compile_str);
    }

    return NULL;
}

static int SendSignalToTarget(void *param)
{
    (void)param;

    if (ACTIVE == g_stop_flag)
    {
        return STOP;
    }

    if (CLIENT_DEAD != g_is_target_alive)
    {
        ++g_is_target_alive;
    }

    kill(g_target_pid, SIGUSR1);

    return SEND_SIGNAL_FREQUENCY;
}

static void GetLifeSign(int signal)
{
    (void)signal;
    g_is_target_alive = RESTART_COUNTER;
}

static int CheckTargetPulse(void *argv)
{

    assert(NULL != argv);

    if (ACTIVE == g_stop_flag)
    {
        return STOP;
    }

    if (PULSE_LIMIT > g_is_target_alive)
    {
        return CHECK_PULSE_FREQUENCY;
    }

    if (CLIENT == g_who_am_i)
    {
        g_is_target_alive = RESTART_COUNTER;
        RebootWD(argv);
    }
    else
    {
        g_is_target_alive = CLIENT_DEAD;
        return STOP;
    }

    return CHECK_PULSE_FREQUENCY;
}

static int RebootWD(void *argv)
{
    int status = 0;

    assert(NULL != argv);

    status = CreateWD(argv);

    SemDecrease(g_semid, 1, 0);

    return status;
}

static int RebootClient(void *argv)
{
    assert(NULL != argv);

    unsetenv(ENV_NAME);
    return execvp(*(const char **)argv, (char *const *)argv);
}

static int Identify(void)
{
    char prog_pid[SIZEOF_OF_PID] = {0};

    sprintf(prog_pid, "%d", getpid());
    if (SUCCESS != setenv(ENV_NAME, prog_pid, REMAIN_VAR))
    {
        return FAIL;
    }

    if (SUCCESS == strcmp(getenv(ENV_NAME), prog_pid))
    {
        return CLIENT;
    }
    else
    {
        return WD;
    }
}

void WDStop(void)
{
    raise(SIGUSR2);
    kill(g_target_pid, SIGUSR2);

    unsetenv(ENV_NAME);
}

static void StopSched(void *sched)
{
    assert(NULL != sched);
    SchedStop((sched_t *)sched);
}

static void ActiveStopFlag(int signal)
{
    (void)signal;
    g_stop_flag = ACTIVE;
}