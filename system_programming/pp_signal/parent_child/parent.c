#include <unistd.h>    /* fork, getppid */
#include <sys/types.h> /* pid_t */
#include <signal.h>    /* USR1, USR2 */
#include <sys/wait.h>  /* wait */
#include <stdio.h>     /* printf */

#define FORK_FAIL (-1)

enum Status
{
    SUCCESS = 0,
    FAIL = 1,
    TRUE = 1,
    FALSE = 0
};

void SendToJunior(int signal);

static pid_t g_child_pid = 0;
static struct sigaction sig;

int main()
{
    char *args[] = {"./child", NULL};

    sig.sa_handler = &SendToJunior;
    sigaction(SIGUSR2, &sig, NULL);

    g_child_pid = fork();
    if (FORK_FAIL == g_child_pid)
    {
        return FAIL;
    }

    if (0 == g_child_pid)
    {

        execvp(args[0], args);
        return FAIL;
    }

    while (1)
    {
        pause();
        printf("ping\n");
    }

    return 0;
}

void SendToJunior(int signal)
{
    (void)signal;
    sleep(1);
    kill(g_child_pid, SIGUSR1);
}