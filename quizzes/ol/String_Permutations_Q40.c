#include <stdio.h>
#include <string.h>

void swap(char *c1, char *c2)
{
	char temp;
	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void permute(char *a, int start, int end)
{
	int i = 0;

	if (start == end)
	{
		printf("%s\n", a);
	}
	else
	{
		for (i = start; i <= end; i++)
		{
			swap(&a[start], &a[i]);
			permute(a, start + 1, end);
			swap(&a[start], &a[i]);
		}
	}
}

int main()
{
	char str[] = "AB";
	int n = strlen(str);
	permute(str, 0, n - 1);
	return 0;
}
