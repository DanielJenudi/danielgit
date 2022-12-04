/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Mariana
 *Date: 22.08.22
 ******************************************************************************/
#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
#include <string.h>     /* memset */
#include <netinet/in.h> /* bond, hton, struct sockaddr_in */
#include <stdlib.h>     /* rand, srand */
#include <time.h>       /* time */

#define MAXLINE 100

int StartUDP(int port);

static void ChatUDP(int sockfd, struct sockaddr_in servaddr);

int main()
{

    StartUDP(8080);
    StartUDP(8090);

    printf("finish\n");

    return 0;
}

int StartUDP(int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    ChatUDP(sockfd, servaddr);

    close(sockfd);
    return 0;
}

static void ChatUDP(int sockfd, struct sockaddr_in servaddr)
{
    char msg_to_send[] = "udp send";

    sendto(sockfd, (const char *)msg_to_send, strlen(msg_to_send),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
}
