/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 21/02/2022
File: Bitwise Operations
Description: ex6
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include<stdio.h>/*printf*/

long Pow2(const unsigned int x, const unsigned int y);
int IsPowerOf2(const unsigned int n);
int IsPowerOf2Loop(const unsigned int n);
int addOne(int x);
void Selector3 (unsigned int *arr, int size);
void TestByteMirrorLoop (unsigned int x);
unsigned int ByteMirrorLoop (unsigned int x);
int If2And6 (unsigned char c);
int IfOneOf2And6 (unsigned char c);
int Swap3And5 (unsigned char c);
void Swap (int *x, int *y);
unsigned int Div16 (unsigned int x);
int CountLoop (unsigned int x);
void PrintFloat (float f);

#define USINT 32

int main()
{
	unsigned int arr[] = {1, 7, 8, 11, 17, 23};
	int x = 5;
	int y = 3;
	
	printf("Pow2: %li\n", Pow2(3, 4));
	printf("IsPowerOf2: %u\n", IsPowerOf2(16));
	printf("IsPowerOf2Loop: %u\n", IsPowerOf2(8));
	printf("addOne: %d\n", addOne(3));
	Selector3(arr, sizeof(arr)/sizeof(unsigned int));
	TestByteMirrorLoop(25);
	printf("If2And6: %d\n", If2And6('b'));
	printf("IfOneOf2And6: %d\n", IfOneOf2And6('b'));
	printf("Swap3And5: %d\n", Swap3And5(16));
	printf("Swap:\nx = %d y = %d\n", x, y);
	Swap(&x, &y);
	printf("x = %d y = %d\n", x, y);
	printf("Div16: %d\n", Div16(33));
	printf("CountLoop: %d\n", CountLoop(7));
	PrintFloat(23.57);
	
	return 0;
}

long Pow2(const unsigned int x, const unsigned int y)
{
	return x << y;
}

int IsPowerOf2(const unsigned int n)
{
	return !(n & (n - 1));
}

int IsPowerOf2Loop(const unsigned int n)
{
	unsigned int base = 2;

	while(n > base)
	{
		base <<= 1;
	} 
	
	return (n == base);	
}

int addOne(int x)
{
    int m = 1;

    while(x & m)
    {
        x = x ^ m;
        m <<= 1;
    }
     
    x ^= m;
    return x;
}

void Selector3 (unsigned int *arr, int size)
{
	unsigned int temp  = 0;
	int count = 0;
	int i = 0;
	
	printf("Selector3: ");
	
	while(i != (size - 1))
	{
		temp = *(arr + i);
		
		while(temp != 0)
		{
			if(1 & temp)
			{
				++count;
			}
			temp >>= 1;
		}
		
	 	if(3 == count)
	 	{
	 		printf("%u, ", *(arr + i));
	 	}
	 	count = 0;
	 	++i;
	 }	
	 printf("\n");
}

unsigned int ByteMirrorLoop (unsigned int x)
{
	unsigned int mirror = 0; 
	int i = USINT - 1;
	
	while(0 != x)
	{
		if(1 & x)
		{
			mirror += 1;
		}
		mirror <<= 1;
		x >>= 1;
		--i;
	}
		
	return mirror << i;
} 

void TestByteMirrorLoop (unsigned int x)
{

	unsigned int mirror = 0; 
	unsigned int i = 0;
	mirror = ByteMirrorLoop(x);
	
	printf("ByteMirrorLoop: start number:  ");
	for(i = 1 << (USINT - 1); i > 0; i /= 2)
	{
		if((x & i) > 0)
		printf("1");
		else
		printf("0");	
	}
	            
	printf("\n________________mirror number: ");
	for(i = 1 << (USINT - 1); i > 0; i /= 2)
	{
		if((mirror & i) > 0)
		printf("1");
		else
		printf("0");	
	}
	printf("\n");
}

int If2And6 (unsigned char c)
{
	return ((1 & c >> 1) & (1 & c >> 5));
}

int IfOneOf2And6 (unsigned char c)
{
	return ((1 & c >> 1) | (1 & c >> 5));
}

int Swap3And5 (unsigned char c)
{
	int bit1 = 0;
	int bit2 = 0;
	int buffer = 0;
	
	bit1 = (1 & c >> 2);
	bit2 = (1 & c >> 4);
	buffer = bit1 ^ bit2;
	buffer = (buffer << 2) | (buffer << 4);
	
	return c ^ buffer;
}

void Swap (int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

unsigned int Div16 (unsigned int x)
{
	int count = 0;
	
	if(16 > x)
	{
		return 0;
	}
	
	while(0 != x)
	{
		++count;
		x >>= 1;
	}
	
	return ((x + 1) << (count - 1));
}

int CountLoop (unsigned int x)
{
	int count = 0;
	
	while(0 != x)
	{
		if(1 & x)
		{
			++count;
		}
		x >>= 1;
	}
	
	return count;
}

void PrintFloat (float f)
{	
	int *ptr_f;
	int i = 0;
	
	ptr_f = (int *)(&f);
	
	printf("%d\n", *ptr_f);

	printf("PrintFloat: ");
	
	for(i = (USINT - 1); i >= 0; --i)
	{
		if(*ptr_f & (1 << i))
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	} 		
	
	printf("\n");		
}

