/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 30/06/2022
File: WatchDog
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>
#include <unistd.h>

#include "wd.h"
#include "semaphores.h"

int main(int argc, const char *argv[])
{
    int semid = 0;

    (void)argc;
    printf("start status - %d\n", WDStart(argv));

    semid = SemCreate("/", 'a', 0);

    printf("\nsemid for stop: %d\n", semid);

    while (0 == SemView(semid))
        ;

    WDStop();

    while (1 == SemView(semid))
        ;

    SemDestroy(semid);

    return 0;
}
