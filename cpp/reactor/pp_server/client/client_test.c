#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */

#include "client.h"

int main(int argc, char *argv[])
{
    (void)argc;

    if (0 == strcmp(argv[1], "1"))
    {
        printf("UDP Start\n");
        printf("UDP client resturn value: %d\n", StartUDP(8080));
    }
    else if (0 == strcmp(argv[1], "2"))
    {
        printf("TCP Start\n");
        printf("TCP client resturn value: %d\n", StartTCP(8090));
    }
    else
    {
        printf("unvalid input\n");
    }

    return 0;
}