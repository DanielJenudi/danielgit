/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Mariana
 *Date: 22.08.22
 ******************************************************************************/

#include <stdio.h> /* printf */

#include "loger.h"

int main()
{
    size_t i = 0;

    for (i = 0; i < 10; ++i)
    {
        printf("ret val: %d\n", LogWrite("./protocol.txt", "hello "));
    }
    return 0;
}