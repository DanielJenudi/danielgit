#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

#include "vsa.h"

#define WORD_SIZE sizeof(size_t)
#define ALIGN_SIZE(size)((size / WORD_SIZE) * WORD_SIZE)

static void RunTest(int test);
void SimpleTest(void);
void ExtremeTest(void);

int main()
{
	printf("~~~ ExtremeTest ~~~\n");
	ExtremeTest();
	printf("~~~ SimpleTest ~~~\n");
	SimpleTest();
	
	return 0;
}

void ExtremeTest(void)
{
	void *block1 = NULL, *block2 = NULL, *block3 = NULL, *block4 = NULL;
	size_t pool_size = 100;
	void *mem_pool = malloc(pool_size);
	vsa_t *vsa = VSAInit(mem_pool, pool_size);
	
	printf("\nvsa: %ld\n", *(long *)mem_pool);
	
	printf("\ninit:\n");
	printf("largest: %ld\n", VSALargestFreeBlock(vsa));
	RunTest((ALIGN_SIZE(pool_size) - 16) == VSALargestFreeBlock(vsa));
	
	
	block1 = VSAAlloc(vsa, 16);
	printf("alloc block1:\n");
	RunTest(56 == VSALargestFreeBlock(vsa));
	
	block2 = VSAAlloc(vsa, 16);
	printf("alloc block2:\n");
	RunTest(32 == VSALargestFreeBlock(vsa));
	
	block3 = VSAAlloc(vsa, 32);
	printf("alloc block3:\n");
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	VSAFree(block2);
	VSAFree(block3);
	
	printf("free all:\n");
	
	block1 = VSAAlloc(vsa, 80);
	printf("alloc block1, alloc max:\n");
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	printf("free max:\n");
	
	block1 = VSAAlloc(vsa, 56);
	printf("alloc block1:\n");
	RunTest(16 == VSALargestFreeBlock(vsa));
	
	block2 = VSAAlloc(vsa, 16);
	printf("alloc block2:\n");
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	block4 = VSAAlloc(vsa, 32);
	printf("alloc block3:\n");
	RunTest(NULL == block4);
	
	VSAFree(block1);
	VSAFree(block2);
	VSAFree(block3);
	
	printf("free all:\n");
	
	printf("alloc all, 8 bytes should add to last alloc\n");
	block1 = VSAAlloc(vsa, 8);
	block2 = VSAAlloc(vsa, 16);
	block3 = VSAAlloc(vsa, 8);
	block4 = VSAAlloc(vsa, 16);
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	VSAFree(block2);
	VSAFree(block3);
	VSAFree(block4);
	
	printf("largest: %ld\n", VSALargestFreeBlock(vsa));
	
	printf("free all succes\n");
	RunTest(80 == VSALargestFreeBlock(vsa));

	printf("alloc all with unalign, 8 bytes should add to last alloc\n");
	block1 = VSAAlloc(vsa, 7);
	block2 = VSAAlloc(vsa, 15);
	block3 = VSAAlloc(vsa, 7);
	block4 = VSAAlloc(vsa, 15);
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	VSAFree(block2);
	VSAFree(block3);
	VSAFree(block4);
	
	printf("free all succes\n");
	RunTest(80 == VSALargestFreeBlock(vsa));
	
	printf("alloc all, 8 bytes should add to last alloc\n");
	block1 = VSAAlloc(vsa, 8);
	block2 = VSAAlloc(vsa, 16);
	block3 = VSAAlloc(vsa, 8);
	block4 = VSAAlloc(vsa, 16);
	RunTest(0 == VSALargestFreeBlock(vsa));
	
	VSAFree(block2);
	VSAFree(block3);
	VSAFree(block4);
	
	printf("partly free and 3 defrag alloc\n");
	block2 = VSAAlloc(vsa, 40);
	
	RunTest(16 == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	VSAFree(block2);
	
	printf("free all succes\n");
	RunTest(80 == VSALargestFreeBlock(vsa));
	
	
	/*printf("vsa: %ld\n", *(long *)mem_pool);
	printf("block1: %ld\n", *(long *)((char *)block1 - 8));
	printf("block2: %ld\n", *(long *)((char *)block2 - 8));
	printf("block3: %ld\n", *(long *)((char *)block3 - 8));
	printf("block4: %ld\n", *(long *)((char *)block4 - 8));
	*/
	
	free(mem_pool);
}

void SimpleTest(void)
{
	void *block1 = NULL, *block2 = NULL, *block3 = NULL;
	size_t pool_size = 1040;
	void *mem_pool = malloc(pool_size);
	
	vsa_t *vsa = VSAInit(mem_pool, pool_size);
	printf("\nLargest Free Block Should Be (pool_size - 16): ");
	RunTest((pool_size - 16) == VSALargestFreeBlock(vsa));
	
	block1 = VSAAlloc(vsa, 504);
	printf("Largest Free Block Should Be (pool_size - 512 - 16): ");
	RunTest((pool_size - 512 - 16) == VSALargestFreeBlock(vsa));
	
	block2 = VSAAlloc(vsa, 248);
	printf("Largest Free Block Should Be (pool_size - 512 - 256 - 16): ");
	RunTest((pool_size - 512 - 256 - 16) == VSALargestFreeBlock(vsa));
	
	block3 = VSAAlloc(vsa, 504);
	printf("Block3 Should Be NULL: ");
	RunTest(NULL == block3);
	
	VSAFree(block2);
	printf("Largest Free Block Should Be (pool_size - 512 - 16): ");
	RunTest((pool_size - 512 - 16) == VSALargestFreeBlock(vsa));
	
	VSAFree(block1);
	printf("Largest Free Block Should Be (pool_size - 16): ");
	RunTest((pool_size - 16) == VSALargestFreeBlock(vsa));
	
	free(mem_pool);
}

static void RunTest(int test)
{
	if (1 == test)
	{
		printf("\x1b[0;34m");
		printf("OK!\n\n");
		printf("\x1b[0m");
	}
	else
	{
		printf("\x1b[1;35m");
		printf("\nTest Failed!\n\n");
		printf("\x1b[0m");
	}
}



