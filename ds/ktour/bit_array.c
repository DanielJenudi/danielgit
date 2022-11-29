/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir Topaz
Date: 03/03/2022
File: Data struct - Bit Array
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <assert.h>/*assert*/
#include <limits.h>/*CHAR_BIT*/
#include "bit_array.h"

#define BITARR_T_SIZE (sizeof(bit_arr_t) * CHAR_BIT)
#define LAST_BIT_ON UINT64_MAX

char *BitArrToString(bit_arr_t arr, char *dest)
{
	uint64_t i = 0;
	char *runner = dest;

	assert(NULL != dest);

	for (i = LAST_BIT_ON; i > 0; i >>= 1)
	{
		*runner = (0 == (arr & i) ? '0' : '1');
		++runner;
	}

	*runner = '\0';

	return dest;
}

bit_arr_t BitArrSetBitOn(bit_arr_t arr, uint64_t index)
{
	assert(index < BITARR_T_SIZE);
	return arr | (uint64_t)1 << index;
}

bit_arr_t BitArrSetBitOff(bit_arr_t arr, uint64_t index)
{
	assert(index < BITARR_T_SIZE);
	return arr & (~((uint64_t)1 << index));
}

int BitArrGetBitVal(bit_arr_t arr, uint64_t index)
{
	assert(index < BITARR_T_SIZE);
	return 0 != (arr & (uint64_t)1 << index);
}

bit_arr_t BitArrFlipBit(bit_arr_t arr, uint64_t index)
{
	assert(index < BITARR_T_SIZE);
	return arr ^ ((uint64_t)1 << index);
}

bit_arr_t BitArrFlipAll(bit_arr_t arr)
{
	return arr ^ ~(uint64_t)0;
}

bit_arr_t BitArrRotateArrR(bit_arr_t arr, uint64_t shift)
{
	bit_arr_t arr_end;

	shift %= BITARR_T_SIZE;

	arr_end = arr << (BITARR_T_SIZE - shift);
	arr = arr >> shift;

	return arr | arr_end;
}

bit_arr_t BitArrRotateArrL(bit_arr_t arr, uint64_t shift)
{
	bit_arr_t arr_start;

	shift %= BITARR_T_SIZE;

	arr_start = arr >> (BITARR_T_SIZE - shift);
	arr = arr << shift;

	return arr | arr_start;
}

uint64_t BitArrCountOn(bit_arr_t arr)
{
	uint64_t count = 0;

	while (arr > 0)
	{
		arr &= arr - 1;
		++count;
	}

	return count;
}

uint64_t BitArrCountOff(bit_arr_t arr)
{
	return BITARR_T_SIZE - BitArrCountOn(arr);
}

bit_arr_t BitArrSetAll(bit_arr_t arr)
{
	(void)arr;
	return ~0;
}

bit_arr_t BitArrResetAll(bit_arr_t arr)
{
	(void)arr;
	return 0;
}

bit_arr_t BitArrSetBit(bit_arr_t arr, uint64_t index, int bool_val)
{
	assert(index < BITARR_T_SIZE);

	if (BitArrGetBitVal(arr, index) != bool_val)
	{
		arr = BitArrFlipBit(arr, index);
	}

	return arr;
}

bit_arr_t BitArrMirror(bit_arr_t arr)
{
	bit_arr_t mirror = 0;
	uint64_t count = 0;
	uint64_t i = 0;

	for (i = LAST_BIT_ON; i > 0; i >>= 1)
	{
		if (0 != (arr & i))
		{
			mirror = BitArrSetBitOn(mirror, count);
		}
		++count;
	}
	return mirror;
}

bit_arr_t BitArrSwap2Bit(bit_arr_t arr, uint64_t index1, uint64_t index2)
{
	assert(index1 < BITARR_T_SIZE);
	assert(index2 < BITARR_T_SIZE);

	if (BitArrGetBitVal(arr, index1) != BitArrGetBitVal(arr, index2))
	{
		arr = BitArrFlipBit(arr, index1);
		arr = BitArrFlipBit(arr, index2);
	}

	return arr;
}
