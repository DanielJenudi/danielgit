#include <stdio.h>/* printf */

int *Product(int *arr, int *result, size_t size);


int main()
{
	int arr[] = {2, 3, 4};
	int result[3];
	size_t i = 0;
	size_t size = 3;
	
	Product(arr, result, size);
	
	for(i = 0; i < size; ++i)
	{
		printf("arr in place %lu: %d\n", i, result[i]);
	}
		
	return 0;
}

int *Product(int *arr, int *result, size_t size)
{
	size_t i = 0;
	int prod = 0;
	int *res_r = NULL; 
	int *arr_r = NULL;

	res_r = result + (size - 2);
	arr_r = arr + (size - 2);
	prod = *(arr + size - 1);


	for(i = 0; i < (size - 1); ++i)
	{
		*res_r = prod;
		prod *= *arr_r;
		--arr_r;
		--res_r;
	}
	
	*(result + size - 1) = 1;
	res_r = result + 1;
	arr_r = arr + 1;
	prod = *arr;
	
	for(i = 0; i < (size - 1); ++i)
	{
		*res_r *= prod;
		prod *= *arr_r;
		++arr_r;
		++res_r;
	}

	return result;
}






