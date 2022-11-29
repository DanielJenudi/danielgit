
// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int broadcast = 1;
    int sockfd;
    char buffer[MAXLINE];
    char *msg_to_server = "ping";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                   sizeof(broadcast)) == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "10.1.0.106", &(servaddr.sin_addr));
    // servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    servaddr.sin_port = htons(PORT);

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