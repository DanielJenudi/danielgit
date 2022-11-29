#include <stdio.h>
#include <string.h>
#include <assert.h>


int Find(char *arr, size_t size, int c)
{
	long result = 1;
	
	while(0 < size)
	{
		result *= *arr - c;
		++arr;
		--size;
		result = !!result;
	}
	
	return !result;
}


size_t gcd(size_t a, size_t b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

static void Swap(char *c1, char *c2)
{
	char temp = *c1;

	*c1 = *c2;
	*c2 = temp;
}

static void Reverse(char *begin, char *end)
{
	while(begin < end)
	{
		Swap(begin, end);
		++begin;
		--end;
	}
}

void CircularShift(char arr[], size_t n, size_t size)
{
	assert(NULL != arr);

	Reverse(arr, arr + size - n - 1);
	Reverse(arr + size - n, arr + size - 1);
	Reverse(arr, arr + size -1);
}

int main(void)
{
/*****Find Test*****/
	{
		char arr[] = {'a', 'b', 'c', 'd', 'e'};

		Find(arr, sizeof(arr) / sizeof(char), 'c') ? puts("is there :)") : 
													 puts("is not there :(");

		Find(arr, sizeof(arr) / sizeof(char), 'f') ? puts("is there :)") : 
													 puts("is not there :(");

		Find(arr, sizeof(arr) / sizeof(char), 'e') ? puts("is there :)") : 
													 puts("is not there :(");

		Find(arr, sizeof(arr) / sizeof(char), 'a') ? puts("is there :)") : 
													 puts("is not there :(");
	}

/*****CircularShift Test*****/
	{
		int i = 0;
		char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

		printf("for n = 3 and arr: ");
		for(i = 0; 8 > i; ++i)
		{
			putchar(arr[i]);
		}
		puts(", the rotation is:");
		CircularShift(arr, 3, 8);
		
		for(i = 0; 8 > i; ++i)
		{
			putchar(arr[i]);
		}
		puts("");
	}

	return 0;
}
