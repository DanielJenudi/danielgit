/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Mariana
 *Date: 22.08.22
 ******************************************************************************/
#include <stdio.h>      /* perror */
#include <unistd.h>     /* close */
#include <string.h>     /* bzero */
#include <netinet/in.h> /* bond, hton, struct sockaddr_in */
#include <sys/types.h>  /* fd_set */
#include <sys/time.h>   /* struct timeval */

#include "server.h"
#include "loger.h"

#define MAX(Y, X) ((Y) > (X) ? (Y) : (X))
#define STDIN_FD (0)
#define MAXLEN (1024)
#define NUMOFTCPLISTEN (5)

enum Ret_Val
{
    TIME_REACH_OUT = 0,
    SUCCESS = 0,
    FAIL = -1,
    EXIT = 1
};

enum True_False
{
    FALSE = 0,
    TRUE = 1
};

enum Time_Limit
{
    SECOND = 7,
    MICROSECOND = 0
};

/********** Init **********/

static int InitServerUDP(int port);
static int InitServerTCP(int port);
static void InitFDSet(fd_set *set, int udp_fd, int tcp_fd, int *max_fd);
static void InitSelectTime(struct timeval *tv);

/********** Handlers **********/

static int SearchAndHandle(fd_set *set, fd_set *res_set, int udp_fd, int tcp_fd,
                           int *max_fd);
static int HandleStdIn();
static int HandleUDP(int udp_fd);
static int HandleNewTCP(fd_set *res_set, int tcp_fd, int *max_fd);
static int TCPSearchFDAndHandle(fd_set *res_set, fd_set *set, int *max_fd);
static int HandleTCPRecive(fd_set *res_set, int *max_fd, int fd);
static int RemoveFD(fd_set *res_set, int *max_fd, int fd);

/********** Global Var **********/

static const char g_msg_pong[] = "pong\n";
static const char g_msg_unrecognize[] = "Unrecognize Message\n";

/********** Server **********/

int StartServer(int udp_port, int tcp_port)
{
    int udp_fd = 0;
    int tcp_fd = 0;
    int max_fd = 0;

    int select_retval = 0;
    int handler_retval = 0;

    fd_set res_select_set;
    fd_set select_set;
    struct timeval tv;

    udp_fd = InitServerUDP(udp_port);
    if (FAIL == udp_fd)
    {
        perror("Init UDP failed");
        return FAIL;
    }

    tcp_fd = InitServerTCP(tcp_port);
    if (FAIL == tcp_fd)
    {
        perror("Init TCP failed");
        return FAIL;
    }

    InitFDSet(&res_select_set, udp_fd, tcp_fd, &max_fd);

    while (SUCCESS == handler_retval)
    {
        InitSelectTime(&tv);
        select_set = res_select_set;

        select_retval = select(max_fd + 1, &select_set, NULL, NULL, &tv);

        switch (select_retval)
        {
        case (FAIL):
        {
            perror("select fail");
            handler_retval = FAIL;
            break;
        }
        case (TIME_REACH_OUT):
        {
            LogWrite("./protocol.txt", "server : time reach out");
            break;
        }
        default:
        {
            handler_retval = SearchAndHandle(&select_set, &res_select_set,
                                             udp_fd, tcp_fd, &max_fd);
        }
        }
    }

    close(udp_fd);
    close(tcp_fd);

    if (FAIL == handler_retval)
    {
        perror("Exit with fail\n");
        return FAIL;
    }

    return SUCCESS;
}

/********** Handlers **********/

static int SearchAndHandle(fd_set *set, fd_set *res_set, int udp_fd, int tcp_fd,
                           int *max_fd)
{
    if (TRUE == FD_ISSET(STDIN_FD, set))
    {
        return HandleStdIn();
    }

    if (TRUE == FD_ISSET(udp_fd, set))
    {
        return HandleUDP(udp_fd);
    }

    if (TRUE == FD_ISSET(tcp_fd, set))
    {
        return HandleNewTCP(res_set, tcp_fd, max_fd);
    }

    return TCPSearchFDAndHandle(res_set, set, max_fd);
}

static int HandleStdIn()
{
    char msg_recived[MAXLEN];

    if (0 > read(STDIN_FD, msg_recived, MAXLEN))
    {
        return FAIL;
    }

    msg_recived[strlen(msg_recived) - 1] = '\0';
    LogWrite("./protocol.txt", msg_recived);

    if (0 == strcmp("exit", msg_recived))
    {
        return EXIT;
    }

    if (0 == strcmp("ping", msg_recived))
    {
        write(STDIN_FD, g_msg_pong, sizeof(g_msg_pong));
    }
    else
    {
        write(STDIN_FD, g_msg_unrecognize, sizeof(g_msg_unrecognize));
    }

    return SUCCESS;
}

static int HandleUDP(int udp_fd)
{

    char msg_recived[MAXLEN];
    int len = 0;
    int n = 0;
    struct sockaddr_in client_addr;

    memset(&client_addr, 0, sizeof(client_addr));

    len = sizeof(client_addr);

    n = recvfrom(udp_fd, (char *)msg_recived, MAXLEN, MSG_WAITALL,
                 (struct sockaddr *)&client_addr, (socklen_t *)&len);
    msg_recived[n] = '\0';

    LogWrite("./protocol.txt", msg_recived);

    if (0 == strcmp("ping", msg_recived))
    {
        sendto(udp_fd, g_msg_pong, sizeof(g_msg_pong), MSG_CONFIRM,
               (struct sockaddr *)&client_addr, len);
    }
    else
    {
        sendto(udp_fd, g_msg_unrecognize, sizeof(g_msg_unrecognize), MSG_CONFIRM,
               (struct sockaddr *)&client_addr, len);
    }

    return SUCCESS;
}

static int HandleNewTCP(fd_set *res_set, int tcp_fd, int *max_fd)
{
    int new_fd = 0;
    struct sockaddr client_addres;
    int client_len = sizeof(client_addres);

    new_fd = accept(tcp_fd, (struct sockaddr *)&client_addres,
                    (socklen_t *)&client_len);
    if (new_fd < 0)
    {
        perror("server accept failed...\n");
        return FAIL;
    }

    FD_SET(new_fd, res_set);
    *max_fd = MAX(*max_fd, new_fd);

    return SUCCESS;
}

static int TCPSearchFDAndHandle(fd_set *res_set, fd_set *set, int *max_fd)
{
    int i = 0;

    for (i = 0; i <= (*max_fd); ++i)
    {
        if (TRUE == FD_ISSET(i, set))
        {
            return HandleTCPRecive(res_set, max_fd, i);
        }
    }

    perror("Fail to find FD");
    return FAIL;
}

static int HandleTCPRecive(fd_set *res_set, int *max_fd, int fd)
{
    char msg_recived[MAXLEN] = {0};
    int recv_retval = 0;

    recv_retval = recv(fd, msg_recived, MAXLEN, 0);
    if (0 == recv_retval)
    {
        return RemoveFD(res_set, max_fd, fd);
    }

    LogWrite("./protocol.txt", msg_recived);

    if (0 == strcmp("ping", msg_recived))
    {
        send(fd, g_msg_pong, strlen(g_msg_pong), 0);
    }
    else
    {
        send(fd, g_msg_unrecognize, strlen(g_msg_unrecognize), 0);
    }

    return SUCCESS;
}

static int RemoveFD(fd_set *res_set, int *max_fd, int fd)
{
    int i = 0;

    FD_CLR(fd, res_set);

    for (i = (*max_fd); i >= 0; --i)
    {
        if (TRUE == FD_ISSET(i, res_set))
        {
            *max_fd = i;
            return SUCCESS;
        }
    }

    perror("RemoveFD: can't find fd in res_set\n");
    return FAIL;
}

/********** Init **********/

static int InitServerUDP(int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed\n");
        return FAIL;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed\n");
        return FAIL;
    }

    return sockfd;
}

static int InitServerTCP(int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket creation failed...\n");
        return FAIL;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        perror("socket bind failed...\n");
        return FAIL;
    }

    if ((listen(sockfd, NUMOFTCPLISTEN)) != 0)
    {
        perror("Listen failed...\n");
        return FAIL;
    }

    return sockfd;
}

static void InitFDSet(fd_set *set, int udp_fd, int tcp_fd, int *max_fd)
{
    *max_fd = MAX(udp_fd, tcp_fd);

    FD_ZERO(set);
    FD_SET(STDIN_FD, set);
    FD_SET(udp_fd, set);
    FD_SET(tcp_fd, set);
}

static void InitSelectTime(struct timeval *tv)
{
    tv->tv_sec = SECOND;
    tv->tv_usec = MICROSECOND;
}