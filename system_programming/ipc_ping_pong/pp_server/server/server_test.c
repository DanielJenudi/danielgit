/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Mariana
 *Date: 22.08.22
 ******************************************************************************/
#include <stdio.h> /* printf */

#include "server.h"

int main()
{
    printf("Server Start\n");
    printf("return value StartServer: %d\n", StartServer(8080, 8090));

    return 0;
}