#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static void PrintArr(int *arr, size_t size);
static void Swap(int *x, int *y);
static void Shuffle(int *arr, size_t size);

int main()
{
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t size = sizeof(arr)/sizeof(int);
	
	Shuffle(arr, size);
	PrintArr(arr, size);

	return 0;
}

static void Shuffle(int *arr, size_t size)
{
	int index1 = 0;
	int index2 = 0;
	size_t i = 0;
	
	srand(time(NULL));
	
	for(i = 0; i < size; ++i)
	{
		index1 = rand() % size;
		index2 = rand() % size;
		
		Swap(&arr[index1], &arr[index2]);
	}
}

static void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

static void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		printf("%d\n", arr[i]);
	} 
}
