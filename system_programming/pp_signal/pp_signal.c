#include <unistd.h>    /* fork, getppid */
#include <sys/types.h> /* pid_t */
#include <signal.h>    /* USR1, USR2 */
#include <sys/wait.h>  /* wait */
#include <stdio.h>     /* printf */

#include "pp_signal.h"

#define WAIT_FAIL (-1)
#define FORK_FAIL (-1)

enum Status
{
    SUCCESS = 0,
    FAIL = 1,
    TRUE = 1,
    FALSE = 0
};

static pid_t g_child_pid = 0;
static pid_t g_parent_pid = 0;

struct sigaction sig1;
struct sigaction sig2;

void Sig1(int signal);
void Sig2(int signal);

int Play()
{
    size_t i = 0;

    sig1.sa_handler = &Sig1;
    sig2.sa_handler = &Sig2;

    sigaction(SIGUSR1, &sig1, NULL);
    sigaction(SIGUSR2, &sig2, NULL);

    g_parent_pid = getpid();
    g_child_pid = fork();
    if (FORK_FAIL == g_child_pid)
    {
        return FAIL;
    }

    if (0 == g_child_pid)
    {
        kill(g_parent_pid, SIGUSR2);
    }

    while (1)
    {
        pause();
    }

    return 0;
}

void Sig1(int signal)
{
    (void)signal;
    printf("pong\n");
    sleep(1);
    kill(g_parent_pid, SIGUSR2);
}

void Sig2(int signal)
{
    (void)signal;
    printf("ping\n");
    sleep(1);
    kill(g_child_pid, SIGUSR1);
}
