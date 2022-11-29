/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 16/02/2022
File: Files
Description: Exercise 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include<stdio.h>/*printf*/
#include<string.h>/*strcmp*/
#include<stdlib.h>/*exit*/

#define SIZE 5
#define MAXSTR 100

int CompereBegining (const char *file_name);
int Compere (const char *file_name);
int Remove ();
int Count ();
int Exit ();
int Begining ();
int Write ();

enum check{SUCCESE, FAIL};

typedef struct handler
{
	char *name;
	int (*cmp)(const char *);
	int (*operate)();
} handler;

/*global variables*/
FILE *g_fp = NULL;
char *g_file_name = NULL;
char g_str[MAXSTR];

int main(int argc, char *argv[])
{
	handler arr_handler[SIZE] = {
	{"-remove\n", Compere, Remove}, 
	{"-count\n", Compere, Count}, 
	{"-exit\n", Compere, Exit}, 
	{"<\n", CompereBegining, Begining}, 
	{"-write\n", Compere, Write}
	};
	
	int i = 0;
	
	if(2 != argc) 
	{ 
		printf("No file inserted\n");
		return FAIL;
	}
	
	g_file_name = argv[1];
	
	while(1)
	{
		printf("\nPleas write a string or a command:\n");
		fgets(g_str, MAXSTR, stdin); /*get a strirng*/
		
		while(arr_handler[i].cmp(arr_handler[i].name) && i != SIZE - 1)
		{
			++i;
		}
		arr_handler[i].operate();
		i = 0;
	}	
	
	return SUCCESE;
}

int Compere (const char *file_name)
{
	if(0 == strcmp(file_name, g_str))
	{
		return SUCCESE;
	}
	else
	{
		return FAIL;
	}
}

int CompereBegining (const char *file_name)
{
	if(*file_name == *g_str)
	{
		return SUCCESE;
	}
	else
	{
		return FAIL;
	}
}

int Write ()
{	
	g_fp = fopen(g_file_name, "a");/*open or create the first file in avrgv*/
	
	if(NULL == g_fp)
	{
		printf("Failed to creat a file\n");
		return FAIL;
	}
	
	fputs(g_str , g_fp);/*put the string in the file*/
	fclose(g_fp);/*close the file*/
	
	printf("The string was inserted successfully\n");
	
	return SUCCESE;
}

int Remove ()
{	
	if(NULL == g_fp)
	{
		printf("No file to be remove\n");
		return 	FAIL;
	}

	remove(g_file_name);
	printf("The file had been removed\n");
	
	return SUCCESE;
}

int Count ()
{	
	int count = 0;
	char c;
	
	g_fp = fopen(g_file_name, "r");/*open the file for reding*/
	
	if(NULL == g_fp)
	{
		printf("The file does not exist\n");
		return FAIL;
	}
			
		while(c != EOF)
		{
			c = getc(g_fp);
			
			if(c == '\n')
			{
				++count;
			}
		}
		printf("The numbe of rows in %s file is: %d\n",g_file_name, count);
	
		fclose(g_fp);/*close the file*/
		
		return SUCCESE;
}

int Exit ()
{	
	printf("Goodbay!\n");
	exit(0);
	return FAIL;
}

int Begining ()
{	
	char temp_str[MAXSTR];
	int i = 0;
	char c;
		
	g_fp = fopen(g_file_name, "r");/*open the file fo copying*/
	
	if(NULL == g_fp)
	{
		printf("The file does not exist");
		return FAIL;
	}
	
	fseek(g_fp, 0, SEEK_SET);/*go to the start of the file*/
	
	for( c = getc(g_fp); c != EOF; c = getc(g_fp))
	{
		temp_str[i] = c;
		++i;	
	}
	fclose(g_fp);/*close the file*/
	
	
	g_fp = fopen(g_file_name, "w");/*open the file and erased it*/
	fputs((g_str + 1), g_fp);/*put the string in the file except the '<'*/
	fputs(temp_str , g_fp);/*put the old string in the file*/
	fclose(g_fp);/*close the file*/
	
	printf("successfully inserte to the begining of the file\n");
	
	return SUCCESE;
}



