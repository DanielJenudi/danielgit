/*         _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._
		 ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.
		( (                                                         ) )
		 ) )                                                       ( (
		( (              Author: Daniel Jenudi                      ) )
		 ) )             Date: 3/4/22                              ( (
		( (              Reviewed By: Chen Rudi						) )
		 ) ) 		     File: Fixed Size Allocators	           ( (
		( (			     Description: Source File                   ) )
		 ) )                                                       ( (
		( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )
		 `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'        */

#include <assert.h> /* assert */

#include "fsa.h" /* fsa.h */

#define WORD_SIZE sizeof(size_t)
#define ALING_WORD_SIZE (sizeof(size_t) - 1)

struct fsa
{
	size_t base;
};

static size_t BlockToWord(size_t block_size);
static void InitPool(fsa_t *mem_pool, size_t nblocks, size_t block_size);

size_t FSAReqPoolSize(size_t nblocks, size_t block_size)
{	
	return (BlockToWord(block_size) * (nblocks)) * WORD_SIZE + sizeof(fsa_t);
}

fsa_t *FSAInit(void *mem_pool, size_t nblocks, size_t block_size)
{
	assert(NULL != mem_pool);
	
	InitPool(mem_pool, nblocks, block_size);  
	
	return (fsa_t *)mem_pool;
}

static void InitPool(fsa_t *mem_pool, size_t nblocks, size_t block_size)
{
	size_t jump_index = 1;
	size_t block_in_words = BlockToWord(block_size);
	
	assert(NULL != mem_pool);
	
	/*init base*/
	mem_pool->base = jump_index;
	jump_index += block_in_words;
	++mem_pool;
	/*end of base init*/
	
	while(0 < (nblocks - 1))
	{
		mem_pool->base = jump_index;
		jump_index += block_in_words;
		
		mem_pool = mem_pool + block_in_words;
		--nblocks;
	}
	
	/*init last element*/
	mem_pool->base = 0;
	/*end of last element init*/
}

static size_t BlockToWord(size_t block_size)
{
	assert(block_size != 0);
	
	block_size += ALING_WORD_SIZE;
	return (block_size & ~ ALING_WORD_SIZE) / WORD_SIZE;
}

void *FSAAlloc(fsa_t *pool)
{
	void *alloc = NULL;
	
	assert(NULL != pool);

	if(0 == pool->base)
	{
		return NULL;
	}
	
	alloc = pool + pool->base;
	pool->base = *(size_t *)alloc; 
	
	return alloc;
}

void FSAFree(fsa_t *pool, void *block)
{
	assert(NULL != pool);
	assert(NULL != block);
	
	*(size_t *)block = pool->base;
	pool->base = ((fsa_t *)block - pool);

}

size_t FSACountFreeBlocks(const fsa_t *pool)
{
	size_t count = 0;
	const void *runner = NULL;
	
	assert(NULL != pool);
	
	runner = (const void *)pool;
	
	while(0 != *(const size_t *)runner)
	{
		runner = pool + *(const size_t *)runner;
		++count;
	}

	return count;
}



