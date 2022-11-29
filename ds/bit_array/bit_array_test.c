/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir Topaz
Date: 03/03/2022
File: Data struct - Bit Array
Description: Main file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/
#include "bit_array.h"

void Test_ON_OFF();
void Test_BitArrGetBitVal();
void Test_Flip();
void Test_RotateArrR();
void Test_RotateArrL();
void Test_Count_ON_OFF();
void Test_Set_Reset_All();
void Test_BitArrSetBit();
void Test_BitArrMirror();
void Test_BitArrFlipAll();
void Test_BitArrSwap2Bit();

int main()
{
	Test_ON_OFF();
	Test_BitArrGetBitVal();
	Test_Flip();
	Test_BitArrFlipAll();
	Test_RotateArrR();
	Test_RotateArrL();
	Test_Count_ON_OFF();
	Test_Set_Reset_All();
	Test_BitArrSetBit();
	Test_BitArrMirror();
	Test_BitArrSwap2Bit();

	return 0;
}

void Test_ON_OFF()
{
	bit_arr_t arr = 5;
	char str[65] = "\0";

	printf("bit 1 on: %ld -> %lu:\n", arr, BitArrSetBitOn(arr, 1));
	printf("%s\n", BitArrToString(BitArrSetBitOn(arr, 1), str));

	printf("bit 0 off: %ld -> %lu:\n", arr, BitArrSetBitOff(arr, 0));
	printf("%s\n", BitArrToString(BitArrSetBitOff(arr, 0), str));
}

void Test_BitArrGetBitVal()
{
	bit_arr_t arr = 5;

	printf("\nON\\OFF:\n");

	1 == BitArrGetBitVal(arr, 0) ? printf("ON\n") : printf("OFF\n");
	1 == BitArrGetBitVal(arr, 1) ? printf("ON\n") : printf("OFF\n");
}

void Test_Flip()
{
	bit_arr_t arr = 5;
	char str[65] = "\0";

	printf("\nbefor flip : %s\n", BitArrToString(arr, str));
	printf("after flip : %s\n", BitArrToString(BitArrFlipBit(arr, 5), str));
}

void Test_RotateArrR()
{
	bit_arr_t arr = 6842;
	char str[65] = "\0";

	printf("\nbefor RotateR: %s\n", BitArrToString(arr, str));
	printf("after RotateR: %s\n", BitArrToString(BitArrRotateArrR(arr, 3), str));
}

void Test_RotateArrL()
{
	bit_arr_t arr = 0x8006000400010000;
	char str[65] = "\0";

	printf("\nbefor RotateL: %s\n", BitArrToString(arr, str));
	printf("after RotateL: %s\n", BitArrToString(BitArrRotateArrL(arr, 68), str));
}

void Test_Count_ON_OFF()
{
	bit_arr_t arr = 0x8006000400010000;
	char str[65] = "\0";

	printf("\nNumber : %s\n", BitArrToString(arr, str));
	printf("Count On : %lu\n", BitArrCountOn(arr));
	printf("Count Off : %lu\n", BitArrCountOff(arr));
}

void Test_Set_Reset_All()
{
	bit_arr_t arr = 0x8006000400010000;
	char str[65] = "\0";

	printf("\nNumber : %s\n", BitArrToString(arr, str));
	printf("Reset    : %s\n", BitArrToString(BitArrResetAll(arr), str));
	printf("Set  : %s\n", BitArrToString(BitArrSetAll(arr), str));
}

void Test_BitArrSetBit()
{
	bit_arr_t arr = 5;
	char str[65] = "\0";

	printf("\nNumber        : %s\n", BitArrToString(arr, str));
	printf("Set index 1   : %s\n", BitArrToString(BitArrSetBit(arr, 1, 1), str));
	printf("Reset index 0 : %s\n", BitArrToString(BitArrSetBit(arr, 0, 0), str));
	printf("Set index 0   : %s\n", BitArrToString(BitArrSetBit(arr, 0, 1), str));
}

void Test_BitArrMirror()
{
	bit_arr_t arr = 0x8006000400010000;
	char str[65] = "\0";

	printf("\nNumber : %s", BitArrToString(arr, str));
	printf("\nMirror : %s\n", BitArrToString(BitArrMirror(arr), str));
}

void Test_BitArrFlipAll()
{
	bit_arr_t arr = 0x8006000400010001;
	char str[65] = "\0";

	printf("\nNumber  : %s", BitArrToString(arr, str));
	printf("\nFlipALL : %s\n", BitArrToString(BitArrFlipAll(arr), str));
}

void Test_BitArrSwap2Bit()
{
	bit_arr_t arr = 5;
	char str[65] = "\0";

	printf("\nNumber   : %s", BitArrToString(arr, str));
	printf("\nSwap2Bit : %s\n", BitArrToString(BitArrSwap2Bit(arr, 0, 1), str));
}
