/*****************************************************************************
Name: Daniel Jenudi
*Date: 04/12/22													 			 
*memory_mapping_basics.c														 	 
******************************************************************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy */

int global_val = 1;
const int const_global_val = 2;

static const int const_static_global_val = 3;
static int static_global_val;

static void StaticAddOne(int *num);
void ExternAddOne(int *num);

int main(int argc, char *argv[], char *envp[])
{
    static int static_local_val = 5;
    static const int const_static_local_val = 6;
    int non_const = const_static_local_val;
    
    static char hello[] = "hello";
    int local_val = 7;
    const int const_local_val = 8;
    
    char *str_literal = "Chen Rudy is our Queen";
    
    static int helllo;
    static int hellllllllllo;
    static int hell;
    
    double plz_work[170000];
    
    char *str_heap1 = (char *)malloc(133 * 1024);
    char *str_heap2 = (char *)malloc(133 * 1024);
    char *str_heap3 = (char *)malloc(133 * 1024);
    
    char *str_cmd = argv[1];
    char *str_env = envp[0];
    
    strcpy(str_heap1, "Beitar");
    strcpy(str_heap2, "Jerusalem");
    strcpy(str_heap3, "1936 - 2022");
    
    printf("env: %s\n", str_env);
    printf("cmd: %s\n\n", str_cmd);
    
    printf("str_heap1: %lu\n", str_heap1);
    printf("str_heap2: %lu\n", str_heap2);
    printf("str_heap3: %lu\n\n", str_heap3);
    
    printf("BEFORE local_val: %d\n", local_val);
    StaticAddOne(&local_val);
    printf("AFTER local_val: %d\n", local_val);
    
    free(str_heap1);
    str_heap1 = NULL;
    free(str_heap2);
    str_heap2 = NULL;
    
    return 0;
}

static void StaticAddOne(int *num)
{
    *num += 1;
}

void ExternAddOne(int *num)
{
    StaticAddOne(num);
}

/*
#include <stdlib.h> /* malloc, free 
#include <stdio.h> /* free 
#include <string.h> /* strlen 

static int AddOne(int *x);
int AddTwo(int *x);
int Addthree(int *x);
int Addfour(int *x);

int n_times_addtwo_g = 0;
static int n_times_addthree_g = 0;
static const int limit_g = 10;

int main(int argc, char *argv[], char * envp[])
{
	int *integer = NULL;
	int x = 3;
	int i = 0;
	int *z = (int *)malloc(1000000);
	int *y = (int *)malloc(1000000);
	char *str_cmd = argv[1];
	char *charstr_env = envp[0];



	integer = &x;

	/*integer = (int)strlen(str_cmd);
	
	printf("string %s first letter value: %d", str_cmd, *integer);
	
	AddOne(integer);
	printf("after AddOne: %d\n", *integer);
	AddTwo(integer);
	printf("after AddTwo: %d\n", *integer);
	Addthree(integer);
	printf("after Addthree: %d\n", *integer);
	Addfour(integer);
	printf("after Addfour: %d\n", *integer);

	/**integer = (int)strlen(charstr_env);
	printf("string %s first letter value: %d", charstr_env, *integer);
	
	AddOne(integer);
	printf("after AddOne: %d\n", *integer);
	AddTwo(integer);
	printf("after AddTwo: %d\n", *integer);
	Addthree(integer);
	printf("after Addthree: %d\n", *integer);
	Addfour(integer);
	printf("after Addfour: %d\n", *integer);

	*integer = 1;

	while(i <= limit_g)
	{
		i += AddOne(integer);
		i += AddTwo(integer);
		i += Addthree(integer);
		i += Addfour(integer);
		i -= argc;
	}
	
	printf("last integer result: %d\n", *integer);

	free(z);
	free(y);
	return 0;
}


static int AddOne(int *x)
{
	const int y = 1;
	static int n_times_addone = 0;
	
	int a[1000000];
	
	a[1] = 5;
	printf("%d\n", a[1]);
	*x += y;
	++n_times_addone;
	
	return n_times_addone;
}

int AddTwo(int *x)
{
	int y = 2;
	
	*x += y;
	++n_times_addtwo_g;
	
	return n_times_addtwo_g;
}

int Addthree(int *x)
{
	static const int y = 3;
	
	*x += y;
	++n_times_addthree_g;
	
	return n_times_addthree_g;
}

int Addfour(int *x)
{
	int *y = (int *)malloc(sizeof(int)); 			
	static int n_times_addfour = 0;
	
	*y = 4;
	*x += *y;
	++n_times_addfour;
	
	free(y);
	
	return n_times_addfour;
}


*/



















