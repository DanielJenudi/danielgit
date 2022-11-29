#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;
    int fd2;

    /* FIFO file path */
    char *fifo1 = "/home/daniel/git/system_programming/ipc_ping_pong/fifo_pipe/fifo1";
    char *fifo2 = "/home/daniel/git/system_programming/ipc_ping_pong/fifo_pipe/fifo2";
    char buffer[80];

    size_t i = 0;

    /* Creating the named file(FIFO */
    /* mkfifo(<pathname>, <permission>) */
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    for (i = 0; i < 5; ++i)
    {
        /* Open FIFO for Read only */
        fd1 = open(fifo1, O_RDONLY);
        read(fd1, buffer, sizeof("pong"));
        printf("%s\n", buffer);
        close(fd1);

        sleep(1);

        /* Open FIFO for write only */
        fd2 = open(fifo2, O_WRONLY);
        write(fd2, "pong", strlen("pong") + 1);
        close(fd2);
    }
    return 0;
}