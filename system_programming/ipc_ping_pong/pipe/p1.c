#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

enum PIPE_ARRAY
{
    WRITE = 0,
    READ = 1
};

int main()
{
    int fds1[2];
    int fds2[2];
    pid_t pid;
    FILE *stream1;
    FILE *stream2;
    char buffer[1024];
    size_t i = 0;
    /* Create a pipe. File descriptors for the two ends of the pipe are
    placed in fds. */
    pipe(fds1);
    pipe(fds2);
    /* Fork a child process. */
    pid = fork();
    if (pid == (pid_t)0)
    {

        /* This is the child process. Close our copy of the write end of
        the file descriptor. */
        close(fds1[READ]);
        close(fds2[WRITE]);

        /* Convert the read file descriptor to a FILE object, and read
        from it. */
        stream1 = fdopen(fds1[WRITE], "r");
        stream2 = fdopen(fds2[READ], "w");

        while (!feof(stream1) && !ferror(stream1) && fgets(buffer, sizeof(buffer), stream1) != NULL)
        {
            fputs(buffer, stdout);
            sleep(1);

            fprintf(stream2, "%s\n", "pong");
            fflush(stream2);
        }

        close(fds1[WRITE]);
        close(fds2[READ]);
    }
    else
    {
        /* This is the parent process. */
        /* Close our copy of the read end of the file descriptor. */
        close(fds1[WRITE]);
        close(fds2[READ]);

        /* Convert the write file descriptor to a FILE object, and write
        to it. */
        stream1 = fdopen(fds1[READ], "w");
        stream2 = fdopen(fds2[WRITE], "r");

        for (i = 0; i < 5; ++i)
        {
            fprintf(stream1, "%s\n", "ping");
            fflush(stream1);

            fgets(buffer, sizeof(buffer), stream2);
            fputs(buffer, stdout);
            sleep(1);
        }

        close(fds1[READ]);
        close(fds2[WRITE]);
    }
    return 0;
}