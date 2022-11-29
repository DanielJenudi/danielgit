#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <limits.h> /* LONG_MAX */

#include "vsa.h" /* vsa.h */

#define WORD_SIZE sizeof(size_t)
#define ALING_WORD_SIZE (sizeof(size_t) - 1)
#define BH_SIZE sizeof(block_header_t)
#define ABS(x)((x) > (0) ? (x) : (-x))
#define ALIGN_SIZE(size)((size / WORD_SIZE) * WORD_SIZE)
#define EOVSA LONG_MAX

struct block_header
{
	long metadata; 
};

typedef struct block_header block_header_t;

static size_t BlockToWord(size_t block_size);
static block_header_t *NextBlock(block_header_t *block);

static void *FitAlloc(block_header_t *block);
static void *UnFitAlloc(block_header_t *block, size_t n_bytes);

static long Defrag(block_header_t *block, long n_bytes);

vsa_t *VSAInit(void *m_pool, size_t pool_size)
{
	block_header_t *head = NULL;
	block_header_t *tail = NULL;	
	
	assert(NULL != m_pool);
	assert((2 * BH_SIZE) < pool_size);
	
	pool_size = ALIGN_SIZE(pool_size);
	head = m_pool;
	tail = (block_header_t *)((char *)m_pool + (pool_size - BH_SIZE));
							  
	head->metadata = pool_size - (2 * BH_SIZE);
	tail->metadata = EOVSA;
	
	return 	(vsa_t *)m_pool;
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	block_header_t *runner = NULL;
	
	assert(NULL != vsa);
	
	runner = (block_header_t *)vsa;
	n_bytes = BlockToWord(n_bytes);
	
	while(EOVSA != runner->metadata && Defrag(runner, n_bytes) < (long)n_bytes)
	{
		runner = NextBlock(runner);
	}
	
	if(EOVSA == runner->metadata)
	{
		return NULL;
	}
	
	if((long)n_bytes == runner->metadata)
	{
		return FitAlloc(runner);
	}
	else
	{
		return UnFitAlloc(runner, n_bytes);
	}
}

static void *FitAlloc(block_header_t *block)
{
	void *alloc = NULL;
	
	assert(NULL != block);
	
	alloc = (char *)block + BH_SIZE;
	block->metadata = block->metadata * (-1);
	return alloc;
}

static void *UnFitAlloc(block_header_t *block, size_t n_bytes)
{
	void *alloc = NULL;
	long prev_metadata = 0;
	block_header_t *next = NULL;
	
	assert(NULL != block);
	
	prev_metadata = block->metadata;
	block->metadata = n_bytes * (-1);
	
	alloc = (char *)block + BH_SIZE;
	
	next = NextBlock(block);
	next->metadata = prev_metadata - n_bytes - BH_SIZE;

	return alloc;
}

static size_t BlockToWord(size_t block_size)
{
	assert(block_size != 0);
	
	block_size += (WORD_SIZE - 1);
	
	return (block_size & ~(WORD_SIZE - 1));
}

static block_header_t *NextBlock(block_header_t *block)
{
	assert(NULL != block);
	
	return (block_header_t *)((char *)block + BH_SIZE + ABS(block->metadata));
}

static long Defrag(block_header_t *block, long n_bytes)
{
	block_header_t *runner = NULL;
	
	assert(NULL != block);
	
	runner = NextBlock(block);
	
	if(0 <= block->metadata)
	{
		while (0 <= runner->metadata &&
		       EOVSA != runner->metadata && 
		       block->metadata <= n_bytes)
		{
			block->metadata += (runner->metadata + BH_SIZE);
			runner = NextBlock(runner);
		}
	}
	
	return block->metadata;
}

void VSAFree(void *block)
{
	block_header_t *free = NULL;
	
	assert(NULL != block);
	
	free = (block_header_t *)((char *)block - BH_SIZE);
	free->metadata = ABS(free->metadata);
}

size_t VSALargestFreeBlock(vsa_t *vsa)
{
	block_header_t *runner = NULL;
	long max = 0;
	
	assert(NULL != vsa);
	
	runner = (block_header_t *)vsa;
	
	while(EOVSA != runner->metadata)
	{
		if(max < Defrag(runner, EOVSA))
		{
			max = runner->metadata;
		}
		runner = NextBlock(runner);
	}
	
	return (size_t)max;
}



