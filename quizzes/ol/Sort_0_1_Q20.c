#include <stdio.h>/*printf*/

void SortArr(int *arr, size_t size);

int main()
{
	int arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 1, 0};
	int *runner = arr;
	size_t size = sizeof(arr) / sizeof(int);
	
	SortArr(arr, size);
	
	while(size != 0)
	{
		printf("%d\n", *runner);
		++runner;
		--size;
	}

	return 0;
}

void SortArr(int *arr, size_t size)
{
	int *start = arr;
	int *end = arr + (size - 1);
	
	while(start != end)
	{
		while(start != end && *start == 0)
		{
			++start;
		}
		
		while(start != end && *end == 1)
		{
			--end;
		}
	
		if(start != end)
		{
			*start = 0;
			*end = 1;
		}
	}
}








