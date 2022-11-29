#include <fcntl.h>      // open
#include <iostream>     // cout
#include <sys/types.h>  /* fd_set */
#include <netinet/in.h> /* bond, hton, struct sockaddr_in */
#include <functional>   /* bind */

#include "reactor.hpp"

using namespace ilrd;
using namespace std;

#define NUMOFTCPLISTEN (5)
#define MAXLINE 100

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

static void UDPRecive(int sockfd_udp);
static void UDPReciveAndStop(Reactor *reactor1);

static int InitServerTCP(int port);
static int InitServerUDP(int port);

int main()
{
    Reactor reactor1;

    printf("Server Start\n");
    int sockfd_udp = InitServerUDP(8080);
    int sockfd_udp2 = InitServerUDP(8090);

    reactor1.Add(sockfd_udp, std::bind(&UDPRecive, sockfd_udp), read_t);
    reactor1.Add(sockfd_udp2, std::bind(&UDPReciveAndStop, &reactor1),
                 read_t);

    reactor1.Run();

    reactor1.Remove(sockfd_udp, read_t);
    reactor1.Remove(sockfd_udp2, read_t);

    system("cat ./logger.txt");
    system("> ./logger.txt");

    return 0;
}

static void UDPRecive(int sockfd_udp)
{
    char msg_rec[MAXLINE] = {0};
    int n = 0;
    int len = 0;

    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    cout << "hello\n";

    n = recvfrom(sockfd_udp, (char *)msg_rec, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 (socklen_t *)&len);

    msg_rec[n] = '\0';
    printf("UDP Client: Server responde: %s\n", msg_rec);
}

static void UDPReciveAndStop(Reactor *reactor1)
{

    printf("UDP Client: Server responde: stop\n");

    reactor1->Stop();
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