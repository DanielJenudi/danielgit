/*****************************************************************************
*Name: Amir Litvak													 			 
*Reviewer: Daniel 											 			 
*Date: 04/09/22													 			 
*VSA.c														 			 
******************************************************************************/

#include <assert.h> /* for assert */
#include <limits.h> /* LONG_MIN */
#include <stdlib.h> /* abs */

#include "vsa.h"

#define HELPER (sizeof(size_t) - 1)
#define WORD (sizeof(size_t))
#define BLOCKHEAD sizeof(vsa_t)
#define END LONG_MIN
#define ABS(x)((x) > (0) ? (x) : (-x))

struct block_header
{
	long space;
};


static long Defrag(vsa_t *vsa);
static size_t RealPoolSize(size_t pool_size);
static vsa_t *NextBlockHead(vsa_t *vsa);
static size_t NormalizeUp(size_t n_bytes);

vsa_t *VSAInit(void *m_pool, size_t pool_size)
{
	vsa_t *head = NULL;
	vsa_t *tail = NULL;
	
	assert(NULL != m_pool);
	assert((BLOCKHEAD * 3) < pool_size);
	
	pool_size = RealPoolSize(pool_size);
	head = m_pool;
	tail = (vsa_t *)((char *)m_pool + pool_size - BLOCKHEAD);
	head->space = (pool_size - (BLOCKHEAD * 2));
	tail->space = LONG_MIN;
	
	return head;
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *alloc = NULL;
	vsa_t *runner = NULL;
	vsa_t *next_block = NULL;
	
	assert(NULL != vsa);
	
	n_bytes = NormalizeUp(n_bytes);
	runner = vsa;
	
	while (END != runner->space)
	{
		if (0 < runner->space && (long)n_bytes <= Defrag(runner))
		{
			if ((long)n_bytes < runner->space)
			{
				next_block = (vsa_t *)((char *)runner + n_bytes + BLOCKHEAD);
				next_block->space = runner->space - n_bytes - BLOCKHEAD;
			}
			
			runner->space = -((long)n_bytes);
			alloc = (char *)runner + BLOCKHEAD;
			
			return alloc;
		}
		
		runner = NextBlockHead(runner);
	}
	
	return NULL;
}

void VSAFree(void *block)
{
	vsa_t *to_free = NULL;
	
	if (NULL == block)
	{
		return;
	}
	
	to_free = (vsa_t *)((char *)block - BLOCKHEAD);
	to_free->space = -(to_free->space);
}

size_t VSALargestFreeBlock(vsa_t *vsa)
{
	vsa_t *runner = NULL;
	long largest = 0;
	
	assert(NULL != vsa);
	
	runner = vsa;
	
	while (END != runner->space)
	{
		if (0 < runner->space)
		{
			Defrag(runner);
			largest = (runner->space > largest) ? runner->space : largest;
		}
		
		runner = NextBlockHead(runner);
	}
	
	return (size_t)largest;
}

static long Defrag(vsa_t *vsa)
{
	vsa_t *next = NextBlockHead(vsa);
	
	while (0 <= vsa->space && 0 <= next->space && END != vsa->space)
	{
		vsa->space += next->space + BLOCKHEAD;
		next = NextBlockHead(next);
	}
	
	return vsa->space;
}

static size_t RealPoolSize(size_t pool_size)
{
	pool_size >>= 3;
	
	return (pool_size << 3);
}

static vsa_t *NextBlockHead(vsa_t *vsa)
{
	return (vsa_t *)((char *)vsa + ABS(vsa->space) + BLOCKHEAD);
}

static size_t NormalizeUp(size_t n_bytes)
{
	n_bytes += HELPER;
	
	return (n_bytes & ~HELPER);
}



