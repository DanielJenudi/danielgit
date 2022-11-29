/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom 
Date: 18/05/2022
File: Data struct - Hash Table
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <string.h>/* strlen, strcmp */
#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc, free */

#include "ht.h"

#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

enum status
{
	SUCCESS = 0,
	FAIL
};

size_t HashFunc(const void *data, void *param);
int CmpFunc(const void *new_data, const void *ht_data, void *param);

int IntComper(int x, int y);
int IsNULL(void *data);

void TestHT();
int Dictionary();
void SpellChecker(ht_t *ht);

int main()
{
	printf("********** TestHT **********\n\n");
	TestHT();
	
	Dictionary();
	

	return 0;
}

int Dictionary()
{
    ht_t *ht = NULL;
    FILE *fp = NULL;
    char *buffer = NULL;
    char *start = NULL;
    char *runner = NULL;
    size_t numbytes = 0;
    
    ht = HTCreate(&HashFunc, NULL, &CmpFunc, NULL, 24);
    
    fp = fopen("words.txt", "r");
    if(NULL == fp)
    {
        return 1;
    }
    /*counting bytes in file, then reseting fseek*/
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    buffer = (char *)calloc(numbytes +1, sizeof(char));    
    
    if(NULL == buffer)
    {
        return 1;
    }
    /*reading entire file into buffer*/
    fread(buffer, sizeof(char), numbytes, fp);
    fclose(fp);
    fp = NULL;
    
    /*replacing newline with null terminator and inserting as indevidual words*/
    runner = buffer;
    
     while (NULL != runner)
    {
        start = runner;        
        while('\n' != *runner && '\0' != *runner)
        {
            ++runner;
        }
        if('\0' == *runner)
        {
              break;
        }
        else
        {
            *runner = '\0';
            HTInsert(ht, start);
            ++runner;  
        }     
    }
    
    SpellChecker(ht);

    free(buffer);
    buffer = NULL;
    HTDestroy(ht);
    ht = NULL;
    
    return 0;
}

void SpellChecker(ht_t *ht)
{
	char word[50] = {0};
	char end[50] = "END";
	
	printf("For exit write 'END':\n");
	
	printf("Write Word:\n");
	scanf("%49s", word);
	
	while(strcmp(end, word))
	{
		if(NULL != HTFind(ht, word))
		{
			printf("FOUND\n");
		}
		else
		{
			printf("NOT FOUND\n");
		}
		
		printf("Write Word:\n");
		scanf("%49s", word);
	}
}


void TestHT()
{
	char str1[] = "hello";
	char str2[] = "my";
	char str3[] = "name";
	char str4[] = "is";
	char str5[] = "daniel";
	char str6[] = "jenudi";
	
	char str7[] = "olleh";
	char str8[] = "ym";
	char str9[] = "eman";
	char str10[] = "si";
	char str11[] = "leinad";
	char str12[] = "idunej";

	ht_t *ht = NULL;
	ht = HTCreate(&HashFunc, NULL, &CmpFunc, NULL, 10);
	
	printf("HTCreate: ");
	RUNTEST(IsNULL(ht));
	printf("HTIsEmpty: ");
	RUNTEST(IntComper(HTIsEmpty(ht), 1));
	printf("empty HT HTFind: ");
	RUNTEST(IntComper(IsNULL(HTFind(ht, str7)), 1));
	
	printf("~~~ Start HTInsert ~~~\n\n");
	HTInsert(ht, str1);
	HTInsert(ht, str2);
	HTInsert(ht, str3);
	HTInsert(ht, str4);
	HTInsert(ht, str5);
	HTInsert(ht, str6);
	
	printf("HTSize: ");
	RUNTEST(IntComper(HTSize(ht), 6));
	printf("HTIsEmpty: ");
	RUNTEST(IntComper(HTIsEmpty(ht), 0));
	
	HTInsert(ht, str7);
	HTInsert(ht, str8);
	HTInsert(ht, str9);
	HTInsert(ht, str10);
	HTInsert(ht, str11);
	HTInsert(ht, str12);
	printf("~~~ End HTInsert ~~~\n\n");
	
	printf("HTIsEmpty: ");
	RUNTEST(IntComper(HTIsEmpty(ht), 0));
	printf("HTSize: ");
	RUNTEST(IntComper(HTSize(ht), 12));
	
	printf("HTFind: ");
	RUNTEST(IntComper((HTFind(ht, str1) == str1), 1));
	printf("HTFind: ");
	RUNTEST(IntComper((HTFind(ht, str7) == str7), 1));
	
	printf("~~~ Start HTDelete ~~~\n");
	HTRemove(ht, str7);
	printf("~~~ End HTDelete ~~~\n\n");
	
	printf("HTSize: ");
	RUNTEST(IntComper(HTSize(ht), 11));
	
	printf("HTFind: ");
	RUNTEST(IntComper((HTFind(ht, str1) == str1), 1));
	printf("deleted item HTFind: ");
	RUNTEST(IntComper(IsNULL(HTFind(ht, str7)), 1));
	
	HTDestroy(ht);
}

size_t HashFunc(const void *data, void *param)
{
	(void)param;   
    return strlen((char *)data);
}

int CmpFunc(const void *new_data, const void *ht_data, void *param)
{
    (void)param;
    
    return !!strcmp((char *)new_data, (char *)ht_data);
}

int IsNULL(void *data)
{
	return data == NULL ? 1 : 0;
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

