/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Stav Ben Shushan
Date: 31/05/2022
File: Data struct - Knight Tour
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/* printf */

#include "ktour.h"

enum Status
{
    SUCCESS = 0,
    FAIL
};

#define RUNTEST(test)                                  \
    {                                                  \
        if (0 == test)                                 \
        {                                              \
            printf("\x1b[0;32m\x1b[1m\x1b[7m\x1b[5m"); \
            printf("OK\n\n");                          \
            printf("\x1b[0m");                         \
        }                                              \
        else                                           \
        {                                              \
            printf("\x1b[1;31m\x1b[1m\x1b[7m\x1b[5m"); \
            printf("Test Failed\n\n");                 \
            printf("\x1b[0m");                         \
        }                                              \
    }

int IntComper(int x, int y);

int main()
{
    int tour[64] = {0};
    int i = 0;

    printf("Return status ");
    RUNTEST(IntComper(KnightTour(0, tour), 0));

    for (i = 0; i < 64; ++i)
    {
        printf("Move %d: %d\n", i + 1, tour[i]);
    }

    return 0;
}

int IntComper(int x, int y)
{
    if (x != y)
    {
        return FAIL;
    }

    return SUCCESS;
}