/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 26/02/2022
File: Structs
Description: Macros
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/

#define MAX2(X, Y) (X > Y ? X : Y)
#define MAX3(X, Y, Z) (MAX2(MAX2(X, Y), Z))
#define SIZEOF_VAR(VAR) ((size_t)(&(VAR) + 1) - (size_t)(&(VAR)))
#define SIZEOF_TYPE(TYPE) ((size_t)((TYPE *)0 + 1))
#define OFFSETOF(S, F) ((size_t)&(((S *)0)->F))

void MAX2_Test();
void MAX3_Test();
void SIZEOF_VAR_Test();
void SIZEOF_TYPE_Test();
void OFFSETOF_Test();

int main()
{
	MAX2_Test();
	MAX3_Test();
	SIZEOF_VAR_Test();
	SIZEOF_TYPE_Test();
	OFFSETOF_Test();
	
	return 0;
}

void MAX2_Test()
{
	printf("MAX2: %f\n", MAX2(3.2, 6));
}

void MAX3_Test()
{
	printf("MAX3: %f\n", MAX3(18.3, 120.5, 70));
}

void SIZEOF_VAR_Test()
{
	int x = 15;
	
	printf("SIZEOF_VAR: %ld\n", SIZEOF_VAR(x));
}

void SIZEOF_TYPE_Test()
{
	typedef union Test_numbers
	{
	 	int i;
		float f;
		double d;		
	} numbers;

	typedef struct Test_X
	{
		int i;
		char c;
		double d;
		short s;		
	} X;
	
	typedef struct Test_card
	{
		unsigned int suit : 2;
		unsigned int face_value : 4;		
	} card;
	
	printf("\nSIZEOF_TYPE - numbers: %ld\n", SIZEOF_TYPE(numbers));
	printf("SIZEOF_TYPE - X: %ld\n", SIZEOF_TYPE(X));
	printf("SIZEOF_TYPE - card: %ld\n", SIZEOF_TYPE(card));
}

void OFFSETOF_Test()
{
	typedef struct Test_X
	{
		int i;
		char c;
		double d;
		short s;		
	} X;
	
	printf("\nOFFSETOF: %ld\n", OFFSETOF(X, s));
}


























