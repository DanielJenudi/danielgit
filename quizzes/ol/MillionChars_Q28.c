
#include <stddef.h>/* size_t */
#include <stdio.h>/* printf */

void MillionChar(char c);
void ResetAndPrint(size_t *LUT);
size_t CountBits(long num);

int main()
{

	/* MillionChar test */
	MillionChar('a');
	MillionChar('a');
	MillionChar('c');
	MillionChar('b');
	MillionChar('a');
	MillionChar((char)0);
	
	MillionChar('a');
	MillionChar('b');
	MillionChar('c');
	MillionChar('b');
	MillionChar('z');
	MillionChar((char)0);
	
	
	/* CountBits test */
	printf("CountBits: %lu\n", CountBits(-123));
	printf("CountBits: %lu\n", CountBits(123));
	
	return 0;
}

void MillionChar(char c)
{
	static size_t LUT[256];
	
	if(0 == (int)c)
	{
		ResetAndPrint(LUT);
	}
	else
	{
		*(LUT + (size_t)c) += 1;
	}
}

void ResetAndPrint(size_t *LUT)
{
	int i = 0;
	char c_max = 0;
	size_t n_max = 0;
	
	for(i = 0; i < 256; ++i)
	{
		if(*(LUT + i) > n_max)
		{
			n_max = *(LUT + i);
			c_max = (char)i;
		}
		
		*(LUT + i) = 0;
	}
	
	printf("max ocurrnce of %c is %lu\n", c_max, n_max);
}

size_t CountBits(long num)
{
	size_t count = 0;
	
	if(0 > num)
	{
		num *= (-1);
		++count;
	}
	
	while(0 != num)
	{
		num &= (num - 1);
		++count;
	}
	
	return count;
}



