#include <unistd.h>    /* fork, getppid */
#include <sys/types.h> /* pid_t */
#include <signal.h>    /* USR1, USR2 */
#include <sys/wait.h>  /* wait */
#include <stdio.h>     /* printf */

void SendToPapa(int signal);

struct sigaction sig;

static pid_t g_parent_pid = 0;

/*-D_POSIX_C_SOURCE*/

int main()
{
    g_parent_pid = getppid();
    sig.sa_handler = &SendToPapa;
    sigaction(SIGUSR1, &sig, NULL);

    kill(g_parent_pid, SIGUSR2);

    while (1)
    {
        pause();
        printf("pong\n");
    }

    return 0;
}

void SendToPapa(int signal)
{
    (void)signal;
    sleep(1);
    kill(g_parent_pid, SIGUSR2);
}