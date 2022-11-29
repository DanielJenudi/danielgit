#include <unistd.h>    /* fork, getppid */
#include <sys/types.h> /* pid_t */
#include <signal.h>    /* USR1, USR2 */
#include <sys/wait.h>  /* wait */
#include <stdio.h>     /* printf */

#define FORK_FAIL (-1)

/*-D_POSIX_C_SOURCE=199309L*/

/*
set detach-on-fork off
info inferiors
inferior (number of process in info inferiors)
*/

enum Status
{
    SUCCESS = 0,
    FAIL = 1,
    TRUE = 1,
    FALSE = 0
};

void SignalCatcher(int sig, siginfo_t *info, void *ucontext);

int main()
{
    struct sigaction act;

    /*memset(&act, 0, sizeof(act));*/
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = &SignalCatcher;

    if (sigaction(SIGUSR2, &act, NULL))
    {
        return FAIL;
    }

    while (1)
    {
        pause();
        printf("ping\n");
    }

    return 0;
}

void SignalCatcher(int sig, siginfo_t *info, void *ucontext)
{
    sleep(1);
    kill(info->si_pid, SIGUSR1);
}
