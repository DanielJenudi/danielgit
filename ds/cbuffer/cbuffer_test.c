/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher 
Date: 19/03/2022
File: Data struct - Circular Buffer
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/


#include "cbuffer.h" 

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

    
int TestCreate(void);
int TestWriteRead1(void);
int TestWriteRead2(void);
int TestSize_t(const char *str, size_t expected, size_t result);
int TestInt(const char *str, int expected, int result);
int TestDouble(const char *str, double expected, double result);
int TestChar(const char *str, char expected, char result);
int TestString(const char *str, char *expected, char *result);




int main()
{
	printf("~~~~~~~~~~~~~~~~~~Test for create~~~~~~~~~~~~~~~~~~\n");
    RUNTEST(TestCreate());
    printf("~~~~~~~~~~~~~~~~~~Test Write Read1~~~~~~~~~~~~~~~~~~\n");
    RUNTEST(TestWriteRead1());
    printf("~~~~~~~~~~~~~~~~~~Test Write Read2~~~~~~~~~~~~~~~~~~\n");
    RUNTEST(TestWriteRead2());
	return 0;
}

int TestCreate(void)
{
	int result = 0 ;
	c_buffer_t *cbuf = CBufferCreate(5);
	
	result += TestInt("IsEmpty", 1 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Capacity", 5 , CBufferCapacity(cbuf));
	RUNTEST(result);
	result += TestInt("FreeSpace", 5 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	
	CBufferDestroy(cbuf);

	return result;
}

int TestWriteRead1(void)
{
	int result = 0 ;
	c_buffer_t *cbuf = CBufferCreate(5);
	char str[] = "Hello!";
	char dest[10] = "";
	
	result += TestInt("Capacity", 5 , CBufferCapacity(cbuf));
	RUNTEST(result);
	result += TestInt("FreeSpace", 5 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Write", 3 , CBufferWrite(cbuf , (void *)str , 3));
	RUNTEST(result);
	result += TestInt("FreeSpace", 2 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Write", 0 , CBufferWrite(cbuf , (void *)str , 0));
	RUNTEST(result);
	result += TestInt("Write", 2 , CBufferWrite(cbuf , str + 3 , 4));
	RUNTEST(result);
	result += TestInt("Read", 2 , CBufferRead(cbuf , (void *)dest , 2));
	RUNTEST(result);
	result += TestString("string1", "He" , dest);
	RUNTEST(result);
	result += TestInt("FreeSpace", 2 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Write", 2 , CBufferWrite(cbuf , (void *)str , 4));
	RUNTEST(result);
	result += TestInt("Write", 0 , CBufferWrite(cbuf , (void *)str , 4));
	RUNTEST(result);
	result += TestInt("FreeSpace", 0 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Read", 4 , CBufferRead(cbuf , (void *)dest , 4));
	RUNTEST(result);
	result += TestString("string2", "lloH" , dest);
	RUNTEST(result);
	result += TestInt("Read", 1 , CBufferRead(cbuf , (void *)dest , 3));
	RUNTEST(result);
	result += TestInt("FreeSpace", 5 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Capacity", 5 , CBufferCapacity(cbuf));
	RUNTEST(result);
	
	
	result += TestInt("IsEmpty", 1 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Read", 0 , CBufferRead(cbuf , (void *)dest , 3));
	RUNTEST(result);
	result += TestInt("Write", 5 , CBufferWrite(cbuf , (void *)str , 6));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Read", 5 , CBufferRead(cbuf , (void *)dest , 6));
	RUNTEST(result);
	result += TestString("string3", "Hello" , dest);
	RUNTEST(result);
	result += TestInt("IsEmpty", 1 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Write", 5 , CBufferWrite(cbuf , (void *)str , 6));
	RUNTEST(result);
	result += TestInt("Read", 3 , CBufferRead(cbuf , (void *)dest , 3));
	RUNTEST(result);
	result += TestInt("Write", 3 , CBufferWrite(cbuf , (void *)str , 3));
	RUNTEST(result);
	result += TestInt("Read", 5 , CBufferRead(cbuf , (void *)dest , 8));
	RUNTEST(result);
	
	
	
	CBufferDestroy(cbuf);

	return result;
}

int TestWriteRead2(void)
{
	int result = 0 ;
	c_buffer_t *cbuf = CBufferCreate(11);
	char str[] = "Hello world!";
	char dest[14] = "";
	

	result += TestInt("IsEmpty", 1 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Capacity", 11 , CBufferCapacity(cbuf));
	RUNTEST(result);
	result += TestInt("Write", 9 , CBufferWrite(cbuf , (void *)str , 9));
	RUNTEST(result);
	result += TestInt("FreeSpace", 2 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , CBufferIsEmpty(cbuf));
	RUNTEST(result);
	result += TestInt("Read", 2 , CBufferRead(cbuf , (void *)dest , 2));
	RUNTEST(result);
	result += TestInt("FreeSpace", 4 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestString("string1", "He" , dest);
	RUNTEST(result);
	result += TestInt("Write", 4 , CBufferWrite(cbuf , (void *)str , 6));
	RUNTEST(result);
	result += TestInt("FreeSpace", 0 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestInt("Read", 11 , CBufferRead(cbuf , (void *)dest , 15));
	RUNTEST(result);
	result += TestInt("FreeSpace", 11 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	result += TestString("string2", "llo worHell" , dest);
	RUNTEST(result);
	result += TestInt("Write", 3 , CBufferWrite(cbuf , (void *)str , 3));
	RUNTEST(result);
	result += TestInt("Read", 3 , CBufferRead(cbuf , (void *)dest , 8));
	RUNTEST(result);
	result += TestInt("FreeSpace", 11 , CBufferFreeSpace(cbuf));
	RUNTEST(result);
	
	
	
	
	CBufferDestroy(cbuf);

	return result;
}

int TestSize_t(const char *str, size_t expected, size_t result)
{
	printf("%s\n" , str);
	return !(expected == result);
}
int TestInt(const char *str, int expected, int result)
{
	printf("%s\n" , str);
	return !(expected == result);
}
int TestDouble(const char *str, double expected, double result)
{
	printf("%s\n" , str);
	return !(expected == result);
}
int TestChar(const char *str, char expected, char result)
{
	printf("%s\n" , str);
	return !(expected == result);
}
int TestString(const char *str, char *expected, char *result)
{
	printf("%s\n" , str);
	
	return !!(strcmp(expected,result));
}


