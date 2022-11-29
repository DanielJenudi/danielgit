/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 30/06/2022
File: WatchDog
Description: WatchDog file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h> /* printf */

#include "wd.h"

int main(int argc, const char *argv[])
{
    (void)argc;
    WDStart(argv);

    return 0;
}
