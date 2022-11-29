/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 30/06/2022
File: WatchDog
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef __WD_H__
#define __WD_H__

#include <stddef.h>

int WDStart(const char *compile_str[]);
void WDStop(void);

#endif /*__WD_H__*/