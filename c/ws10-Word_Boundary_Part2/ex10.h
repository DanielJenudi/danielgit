/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 01/03/2022
File: Word Boundary Optimization part2
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __ILRD_EX9_H__
#define __ILRD_EX9_H__

#include <string.h>/*strlen*/
#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/

#define IS_BIG_ENDIAN (*(size_t *)"\0\xff" < 0x0100)

#define ASCII_DIFFERENCE 48
#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_SIZE 256

char *Itoa(int num, char *str);
char *ItoaBase36(int num, char *str, int base);

int Atoi(char *str);
int AtoiBase36(char *str, int base);

void Print3Arr(const char *arr1, const char *arr2, const char *arr3,
	       size_t size1, size_t size2, size_t size3);
	        
void WhichEndian();   

#endif
