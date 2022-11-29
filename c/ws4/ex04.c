#include <stdio.h>
#include <stdlib.h>


void TestIfElse();
void TestSwitcCase();
void TestLUT();
void LutT();
void LutA();
void LutDoNoting();

#define ESC 27
#define MAXASCII 128

typedef void (*func)();

int main()
{	
	func arr[MAXASCII];
	
	system("stty -icanon -echo");
	
	TestIfElse();
	
	TestSwitcCase();

	TestLUT(arr);
	
	system("stty icanon echo");
	
	return 0;
	
}

void TestIfElse()
{
	char c = '0';
	
	printf("\nstart if/else test:\n");
	
	while(ESC != c)
	{
		c = getchar();
			
		if('T' == c)
		{
			printf("\nT-pressed\n");
		}
		
		if('A' == c)
		{
			printf("\nA-pressed\n");
		}
	}
	
	printf("\nIf/Else test ended\n");
}

void TestSwitcCase()
{
	char c = '0';
	
	printf("\nstart Switch/Case test:\n");
	
	while(ESC != c)
	{
		c = getchar();
		
		switch (c)
		{
			
		case 'T':
		
			printf("\nT-pressed\n");
			break;
		
		case 'A':
		
			printf("\nA-pressed\n");
			break;
		}
	}
	
	printf("\nSwitch/Case test ended\n");
}

void TestLUT(func *arr)
{
	char c = '0';
	int i = 0;
	
	for(i = 0; i<MAXASCII; ++i)
	{
		arr[i] = LutDoNoting;
	}
	
	arr[(unsigned int)'A'] = LutA;
	arr[(unsigned int)'T'] = LutT;
	
	printf("\nstart LUT test:\n");
	
	while(ESC != c)
	{
		c = getchar();
		(*arr[(unsigned int)c])();
	}
	
	printf("\nLUT test ended\n");
}


void LutA()
{
	printf("\nA-pressed\n");
}

void LutT()
{
	printf("\nT-pressed\n");
}

void LutDoNoting() {}























