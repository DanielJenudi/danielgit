#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */


void PrintMissing(int *arr, size_t size);
void PrintMissingXOR(int *arr, size_t size);


int main()
{
	int arr[] = {1,2,3,4,5,7,9,10};
	size_t size = 8;
	
	PrintMissing(arr, size);
	PrintMissingXOR(arr, size);
	
	return 0;
}

void PrintMissing(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int found = 0;
	
	for(i = 1; i < (size + 2); ++i)
	{
		for(j = 0; j < size; ++j)
		{
			if(arr[j] == (int)i)
			{
				found = 1;
			}
		}
			if(0 == found)
			{
				printf("%lu\n", i);
			}
			found = 0;
	}
}

void PrintMissingXOR(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int found = 0;
	
	for(i = 1; i < (size + 2); ++i)
	{
		for(j = 0; j < size; ++j)
		{
			if((arr[j] ^ (int)i) == 0)
			{
				found = 1;
			}
		}
			if((0 ^ found) == 0)
			{
				printf("%lu\n", i);
			}
			found = 0;
	}
}















