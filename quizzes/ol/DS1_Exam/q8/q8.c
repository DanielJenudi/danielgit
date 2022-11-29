#include <stdio.h>/* printf */

#define SIZE 1024

void Init(int *arr);
int MissingNumber(int *arr);

int main()
{
	int arr[SIZE -1];
	
	Init(arr);
	
	printf("the missing number is %d\n", MissingNumber(arr));

	return 0;
}

void Init(int *arr)
{
	int i = 0;

	for(i = 0; i < (SIZE - 1); ++i)
	{
		arr[i] = i;
	}
}

int MissingNumber(int *arr)
{
	long sum_of_all = (SIZE - 1) * (SIZE / 2);
	int i = 0;
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		sum_of_all -= arr[i];
	}
	
	return sum_of_all;
}
