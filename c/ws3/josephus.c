#include <stdio.h>
#include <stdlib.h>

int killing (int size);
int *CreatArr (int num);

int main()
{
	int size = 100;
	
	printf("%d\n", killing(size));

	return 0;
}


int killing (int size)
{
	int *person = NULL;
	int winner = 0;
	int sowrd = 0;
	int deads = 0;
	int *forfree = NULL;
	
	deads = size -1;
	
	person = CreatArr(size);
	forfree = person;
	
	while(deads != 0)
	{
		while(*person == 0)
		{
			++person;
		}
		if(*person == -1)
		{
			person -= size;
		}
		else
		{
			if(sowrd == 0)
			{
				sowrd = 1;
				winner = *person;
				++person;
			}
			else
			{
				sowrd = 0;
				*person = 0;
				--deads;
				++person;
			}
		}	
	}
	
	free(forfree);
	forfree = NULL;
	
	return winner;	
}

int *CreatArr (int num)
{
	int *arr = NULL;
	int i = 0;
	
	arr = (int *)calloc(num + 1, sizeof(int));
	
	for (i = 0; i < num; ++i)
	{
		*(arr + i) = i + 1;
	}
	
	*(arr + num) = -1;
	
	return arr;
}


















































