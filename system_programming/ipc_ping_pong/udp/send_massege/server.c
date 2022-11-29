
// Server side implementation of UDP client-server model
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
    char *msg_to_client = "pong";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    inet_pton(AF_INET, "10.1.0.106", &(servaddr.sin_addr));
    // servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); // len is value/result

    size_t i = 0;

    for (i = 0; i < 10; ++i)
    {

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);

        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        sleep(1);

        sendto(sockfd, (const char *)msg_to_client, strlen(msg_to_client),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
               len);
    }

    return 0;
}