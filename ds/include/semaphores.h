/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Stav
Date: 16/06/2022
File: Semaphore
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __SEMAPHRE_H__
#define __SEMAPHRE_H__

#include <stddef.h> /* size_t */

int SemCreate(char *file_path, char id, size_t start_value);
int SemDestroy(int sem_id);
int SemView(int sem_id);
int SemIncrease(int id, int num, int set_undo);
int SemDecrease(int id, int num, int set_undo);

#endif /*__SEMAPHRE_H__*/
