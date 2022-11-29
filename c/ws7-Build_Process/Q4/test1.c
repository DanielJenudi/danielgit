#include <stdio.h>

int global = 5;

int hello()
{
	printf("hello world\n");
	
	return 0;
}

int main()
{
	hello();
	
	return 0;
}

