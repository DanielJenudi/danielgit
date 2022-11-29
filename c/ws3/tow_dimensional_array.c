#include <stdio.h>

void SumArray (int *arr, int *result);
void TestSumArray (int *arr, int *result);

#define ROW 3
#define COLUMN 4

int main()
{

	int arr[ROW][COLUMN] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9 ,10}};
	int result[COLUMN] = {0};

	TestSumArray((int *)arr, result);

	return 0;

}

void SumArray (int *arr, int *result)
{
	int row = 0;
	int column = 0;
	int row_result = 0;
	
	while(row != ROW)
	{
		while(column != COLUMN)
		{
			row_result += *((arr + COLUMN * row) + column);
			++column;
		}
		*result = row_result;
		row_result = 0;
		column = 0;
		++row;
		++result;
	}
}

void TestSumArray (int *arr, int *result)
{
	int i = 0;
	
	SumArray(arr, result);
		
	for(i = 0; i < ROW; ++i)
	{
		printf("sum of row number %d: %d\n",i ,*result);
		++result;
	}
}






