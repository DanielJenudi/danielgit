#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *StrDup(const char *str1);
char **Copy(const char **arr, int size);
char *ToLower(char *new_arr);
void Print (char **arr, int size);
void FreeTheSlaves(char **arr, int size);

extern char **environ;

int main()
{
	int size = 0;
	char **new_arr = NULL;
	
	for( size = 0; environ[size] != NULL; ++size ) {}
	
	new_arr = Copy((const char **)environ, size);
	
	Print(new_arr, size);
	FreeTheSlaves((char **)new_arr, size);
	
	return 0;
}

char **Copy(const char **arr, int size)
{
	
	char **new_arr = NULL;
	int i = 0;
	new_arr = (char **)malloc( size * sizeof(char *) );
	
	if(NULL == new_arr)
	{
		exit(1);
	} 
	
	for( i = 0; i < size; ++i)
	{
		*(new_arr + i) = StrDup(*(arr + i));
	}
	
	return new_arr;
}

char *StrDup(const char *str1)
{
	char *ptr = NULL;
	
	ptr = (char *)calloc(strlen(str1) + 1, sizeof(char));
	
	if(NULL == ptr)
	{
		exit(1);
	} 
	
	strcpy(ptr, str1);
	
	return ptr;
}

char *ToLower(char *new_arr)
{
	int i = 0;
	
	for( i = 0; *(new_arr + i) != '\0'; ++i)
	{
		*(new_arr + i) = tolower(*(new_arr + i));
	}
	
	return new_arr;
}

void Print (char **arr, int size)
{
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%s\n", ToLower(*(arr + i)));
	}	
}

void FreeTheSlaves(char **arr, int size)
{
	int i = 0;
	
	for( i = 0; i < size; ++i)
	{
		free(*(arr + i));
		*(arr + i) = NULL;
	}
	
	free(arr);
	arr = NULL;
}

