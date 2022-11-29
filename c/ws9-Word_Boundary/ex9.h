/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 28/02/2022
File: Word Boundary Optimization
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __ILRD_EX9_H__
#define __ILRD_EX9_H__

#include <stdio.h> /*size_t, printf*/
#include <string.h> /*cheking*/

#define WORD_SIZE 8
#define BYTE_SIZE 8

void *Memset(void *str, int c, size_t n);
void *Memcpy(void *dest, const void * src, size_t n);
void *Memmove(void *str1, const void *str2, size_t n);

#endif
