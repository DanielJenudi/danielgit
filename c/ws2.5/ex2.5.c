#include<string.h>
#include<stdio.h>

int IsPilandrom (char *str);
void SevenBoom (size_t from, size_t to);
int HaveSeven (int num);

int main()
{

	char pilandrom[] = {"Ab+bA"};

	printf("IsPilandrom: %s? %d\n",
	       pilandrom, IsPilandrom(pilandrom));/*check ispilandrom*/

	SevenBoom(1, 20);
	return 0;
}

int IsPilandrom (char *str)
{
	size_t max = 0;
	size_t min = 0;
	
	max = strlen(str) - 1;/*top of the string*/
	
	while( max > min)
	{
		if( *(str + max) != *(str + min) )
		{
			return 0;
		}
		--max;
		++min;
	}
	return 1;
}

void SevenBoom (size_t from, size_t to)
{
	while( from <= to )
	{
		if( 0 == from % 7 || HaveSeven(from) == 1) 
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%lu\n", from);
		}
		++from;
	}
}

int HaveSeven (int num)
{
	while (0 != num)
	{
		if (7 == num % 10)
		{
			return 1;
		}	
		num /= 10;
	}
	return 0;
}
















