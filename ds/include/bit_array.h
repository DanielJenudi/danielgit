/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir Topaz
Date: 03/03/2022
File: Data struct - Bit Array
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __ILRD_BIT_ARRAY_H__
#define __ILRD_BIT_ARRAY_H__

#include <stddef.h>/* NULL */
#include <stdint.h>/* uint64_t */

typedef uint64_t bit_arr_t;

bit_arr_t BitArrSetBitOn(bit_arr_t arr, uint64_t index);
bit_arr_t BitArrSetBitOff(bit_arr_t arr, uint64_t index);
int BitArrGetBitVal(bit_arr_t arr, uint64_t index);
bit_arr_t BitArrFlipBit(bit_arr_t arr, uint64_t index);
bit_arr_t BitArrRotateArrR(bit_arr_t arr, uint64_t shift);
bit_arr_t BitArrRotateArrL(bit_arr_t arr, uint64_t shift);
uint64_t BitArrCountOn(bit_arr_t arr);
uint64_t BitArrCountOff(bit_arr_t arr);
bit_arr_t BitArrSetAll(bit_arr_t arr);
bit_arr_t BitArrResetAll(bit_arr_t arr);
bit_arr_t BitArrMirror(bit_arr_t arr);
char *BitArrToString(bit_arr_t arr, char *dest);
bit_arr_t BitArrSetBit(bit_arr_t arr, uint64_t index, int bool_val);

/*********************************Advance**************************************/

bit_arr_t BitArrFlipAll(bit_arr_t arr);
bit_arr_t BitArrSwap2Bit(bit_arr_t arr, uint64_t index1, uint64_t index2);

#endif
