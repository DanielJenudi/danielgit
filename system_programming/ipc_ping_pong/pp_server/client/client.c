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

#include "client.h"
#include "loger.h"

#define MAXLINE 100

static void ChatTCP(int sockfd);
static void ChatUDP(int sockfd, struct sockaddr_in servaddr);

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

    LogWrite("./protocol.txt", "UDP : Creat UDP success");

    ChatUDP(sockfd, servaddr);

    LogWrite("./protocol.txt", "UDP : UDP Exit");

    close(sockfd);
    return 0;
}

static void ChatUDP(int sockfd, struct sockaddr_in servaddr)
{
    char msg_rec[MAXLINE] = {0};
    char msg_to_send[MAXLINE] = {0};

    int len = 0;
    int n = 0;

    int random = 0;
    int i = 0;

    srand(time(NULL));

    scanf("%[^\n]%*c", msg_to_send);
    LogWrite("./protocol.txt", msg_to_send);

    while (0 != strcmp(msg_to_send, "exit"))
    {
        random = (rand() % 10) + 1;

        for (i = 0; i < random; ++i)
        {
            sendto(sockfd, (const char *)msg_to_send, strlen(msg_to_send),
                   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
                   sizeof(servaddr));

            n = recvfrom(sockfd, (char *)msg_rec, MAXLINE,
                         MSG_WAITALL, (struct sockaddr *)&servaddr,
                         (socklen_t *)&len);

            msg_rec[n] = '\0';
            LogWrite("./protocol.txt", msg_rec);
            printf("UDP Client: Server responde: %s\n", msg_rec);
            sleep(1);
        }

        scanf("%[^\n]%*c", msg_to_send);
        LogWrite("./protocol.txt", msg_to_send);
    }
}

int StartTCP(int port)
{
    int sockfd = 0;
    struct sockaddr_in servaddr = {0};

    /* socket create and verification */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket creation failed...\n");
        return 1;
    }
    LogWrite("./protocol.txt", "TCP : Socket successfully created");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("connection with the server failed...\n");
        return 1;
    }

    LogWrite("./protocol.txt", "TCP : connected to the server");

    ChatTCP(sockfd);

    LogWrite("./protocol.txt", "TCP : TCP Exit");

    close(sockfd);

    return 0;
}

static void ChatTCP(int sockfd)
{
    char msg_rec[MAXLINE];
    char msg_to_send[MAXLINE];

    int random = 0;
    int i = 0;

    srand(time(NULL));

    scanf("%[^\n]%*c", msg_to_send);
    LogWrite("./protocol.txt", msg_to_send);

    while (0 != strcmp(msg_to_send, "exit"))
    {
        random = (rand() % 10) + 1;

        for (i = 0; i < random; ++i)
        {
            memset(msg_rec, 0, sizeof(msg_rec));

            send(sockfd, msg_to_send, strlen(msg_to_send) + 1, 0);

            recv(sockfd, msg_rec, MAXLINE, 0);
            LogWrite("./protocol.txt", msg_rec);
            printf("TCP Client: Server responde: %s\n", msg_rec);
            sleep(1);
        }

        scanf("%[^\n]%*c", msg_to_send);
        LogWrite("./protocol.txt", msg_to_send);
    }
}
