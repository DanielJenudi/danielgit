#include <stdio.h>/*printf*/

int main()
{
	int arr[] = {1, 2, 3, 7, 5, 1};
	int size = 6;
	
	int *start = arr;
	int *end = arr + size - 1;
	
	int sum_s = 0;
	int sum_e = 0;
	
	if(2 >= size)
	{
		printf("not found\n");
	}
	
	while(1 != size)
	{
		if(sum_s > sum_e)
		{
			sum_e += *end;
			--end;
		}
		else
		{
			sum_s += *start;
			++start;
		}
		--size;
	}
	
	sum_s == sum_e ? printf("num in index : %d\n", *start) : printf("not found\n");
	
	return 0; 
}
















