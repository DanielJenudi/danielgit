#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static void Shuffle(int *arr, size_t size);
static void Swap(int *x, int *y);
void ListenList(int *arr, size_t size);

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	size_t size = sizeof(arr) / sizeof(int);
	
	ListenList(arr, size);
	
	return 0;
}

void ListenList(int *arr, size_t size)
{
	while(0 != size)
	{
		Shuffle(arr, size);
		printf("Now Play : %d\n", *arr);
		++arr;
		--size;	
	}
}


static void Shuffle(int *arr, size_t size)
{
	size_t i = 0;
	size_t rand_num = 0;
	
	srand(time(NULL));
	
	for(i = 0; i < size; ++i)
	{
		rand_num = rand() % size;
		Swap((arr + i), (arr + rand_num));
	}
}

static void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


