#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
#include <string.h>     /* bzero */
#include <netinet/in.h> /* bond, hton, struct sockaddr_in */

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *msg_to_server = "ping";
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    size_t i = 0;

    for (i = 0; i < 10; ++i)
    {

        sendto(sockfd, (const char *)msg_to_server, strlen(msg_to_server),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&servaddr,
                     &len);

        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
        sleep(1);
    }

    close(sockfd);
    return 0;
}