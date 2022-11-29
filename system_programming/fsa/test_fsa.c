/*         _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._
		 ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.
		( (                                                         ) )
		 ) )                                                       ( (
		( (              Author: Daniel Jenudi                      ) )
		 ) )             Date: 3/4/22                              ( (
		( (              Reviewed By: Chen Rudi						) )
		 ) ) 		     File: Fixed Size Allocators	           ( (
		( (			     Description: Test File                     ) )
		 ) )                                                       ( (
		( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )
		 `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'        */

#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc, free */

#include "fsa.h" /* fsa.h */

void PrintPool(fsa_t *fsa, size_t num_of_blocks, size_t block_to_word);

int main()
{
	size_t block_size = 25;	
	size_t num_of_blocks = 3;
	size_t num_of_words = 4;
	
	void *pool = malloc(FSAReqPoolSize(num_of_blocks, block_size));
	fsa_t *fsa = FSAInit(pool, num_of_blocks, block_size);
	
	int *a = NULL;
	int *b = NULL;
	int *c = NULL;
	
	printf("FSAReqPoolSize: %lu\n\n", FSAReqPoolSize(num_of_blocks, block_size));
	PrintPool(fsa, num_of_blocks, num_of_words);
	
	
	a = FSAAlloc(fsa);
	b = FSAAlloc(fsa);
	
	*a = 100;
	*b = 200;
	
	PrintPool(fsa, num_of_blocks, num_of_words);
	
	FSAFree(fsa ,b);
	b = NULL;
	
	b = FSAAlloc(fsa);
	c = FSAAlloc(fsa);
	
	if(NULL == FSAAlloc(fsa))
	{
		printf("alloc NULL\n\n") ;
	}
	
	
	*a = 100;
	*b = 500;
	*c = 300;
	
	PrintPool(fsa, num_of_blocks, num_of_words);
	
	
	FSAFree(fsa ,c);
	c = NULL;
	FSAFree(fsa ,a);
	a = NULL;
	FSAFree(fsa ,b);
	b = NULL;
	
	PrintPool(fsa, num_of_blocks, num_of_words);
	
	free(pool);
	pool = NULL;
	
	return 0;
}

void PrintPool(fsa_t *fsa, size_t num_of_blocks, size_t block_to_word)
{
	void *runner = (void *)fsa;
	size_t i = 0;

	printf("free space: %lu\n", FSACountFreeBlocks(fsa));
	printf("base  : %lu\n", *(size_t *)runner);
	runner = (size_t *)runner + 1;
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		printf("node %lu: %lu\n", i + 1, *(size_t *)runner);
		runner = (char *)runner + block_to_word * sizeof(size_t); 
	}
	
	printf("\n");
}




