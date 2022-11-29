#include <stdio.h>

int Atoi(char *str);

int main()
{
	char str1[] = "91234";
	char str2[] = "1003";
	char str3[] = "-12a2";

	printf("%d\n", Atoi(str1));
	printf("%d\n", Atoi(str2));
	printf("%d\n", Atoi(str3));
	
	return 0;
}

int Atoi(char *str)
{
	int positive = 1;
	int result = 0;
	
	if(*str == '-')
	{
		positive = -1;
		++str;
	}
	
	while((int)'0' <= (int)*str && (int)'9' >= (int)*str)
	{	
		result *= 10;
		result += (int)*str - (int)'0';
		++str;
	}

	return positive * result;
}
