/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom 
Date: 18/05/2022
File: Data struct - Hash Table
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h>/* malloc, free */
#include <assert.h>/* assert */

#include "dll.h"
#include "ht.h"

enum
{
	FALSE = 0,
	SUCCESS = 0,
	FAIL = 1,
	TRUE = 1
};

struct ht
{	
	ht_hash_func_t ht_func;
	void *ht_param;
	ht_cmp_func_t cmp;
	void *cmp_param;
	size_t entries;
	dll_list_t **buckets;
};

static int InitBuckets(ht_t *ht, size_t entries);
static dll_iterator_t Search(ht_t *ht, void *data);
static size_t GetBucketIndex(ht_t *ht, void *data);
static void DestroyAllDll(ht_t *ht, size_t num_of_dll);

ht_t *HTCreate(ht_hash_func_t ht_func, void *ht_param,
			   ht_cmp_func_t cmp, void *cmp_param, size_t entries)
{
	ht_t *ht = NULL;
	
	assert(NULL != cmp);
	assert(NULL != ht_func);
	assert(0 < entries);
	
	ht = (ht_t *)malloc(sizeof(ht_t));
	if(NULL == ht)
	{
		return NULL;
	}		
							  
	ht->buckets = (dll_list_t **)malloc((entries * sizeof(dll_list_t *)));
	if(NULL == ht)
	{
		free(ht);
		ht = NULL;
		
		return NULL;
	}
	
	if(SUCCESS != InitBuckets(ht, entries))
	{
		free(ht->buckets);
		ht->buckets = NULL;
	
		free(ht);
		ht = NULL;
		
		return NULL;
	}
	
	/*init ht*/
	ht->ht_func = ht_func;
	ht->ht_param = ht_param;
	ht->cmp = cmp;
	ht->cmp_param = cmp_param;
	ht->entries = entries;

	return ht;
}

static int InitBuckets(ht_t *ht, size_t entries)
{
	size_t i = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < entries; ++i)
	{
		ht->buckets[i] = DLLCreate();
		if(NULL == ht->buckets[i])
		{
			DestroyAllDll(ht, i);
			
			return FAIL;
		}
	}
	
	return SUCCESS;
}

void HTDestroy(ht_t *ht)
{	
	assert(NULL != ht);
	
	DestroyAllDll(ht, ht->entries);
	
	free(ht->buckets);
	ht->buckets = NULL;
	
	free(ht);
	ht = NULL;
}

static void DestroyAllDll(ht_t *ht, size_t num_of_dll)
{
	size_t i = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < num_of_dll; ++i)
	{
		 DLLDestroy(ht->buckets[i]);
		 ht->buckets[i] = NULL;
	}
}

size_t HTSize(const ht_t *ht)
{
	size_t i = 0;
	size_t sum_size = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < ht->entries; ++i)
	{
		sum_size += DLLCount(ht->buckets[i]);
	}
	
	return sum_size;
}

int HTIsEmpty(const ht_t *ht)
{
	size_t i = 0;
	int status = TRUE;
	
	assert(NULL != ht);
	
	for(i = 0; (i < ht->entries) && (TRUE == status); ++i)
	{
		status = DLLIsEmpty(ht->buckets[i]);
	}
	
	return status;
}

int HTInsert(ht_t *ht, void *data)
{
	size_t bucket_index = 0;
	
	assert(NULL != ht);
	
	bucket_index = GetBucketIndex(ht, data);
	return DLLPushBack(ht->buckets[bucket_index], data);
}

void HTRemove(ht_t *ht, void *data)
{
	assert(NULL != ht);
	assert(NULL != data);
	
	DLLRemove(Search(ht, data));
}

void *HTFind(ht_t *ht, void *data)
{
	dll_iterator_t runner_iter = NULL;
	
	assert(NULL != ht);
	assert(NULL != data);
	
	runner_iter = Search(ht, data);
	
	if(NULL != runner_iter)
	{
		return DLLGetData(runner_iter);
	}
	else
	{
		return NULL;
	}
}

static dll_iterator_t Search(ht_t *ht, void *data)
{
	size_t bucket_index = 0;
	dll_iterator_t runner_iter = NULL;
	
	assert(NULL != ht);
	assert(NULL != data);
	
	bucket_index = GetBucketIndex(ht, data);
	
	runner_iter = DLLBegin(ht->buckets[bucket_index]);
	
	while(DLLEnd(ht->buckets[bucket_index]) != runner_iter)
	{
		if(0 == ht->cmp(data, DLLGetData(runner_iter), ht->cmp_param))
		{
			return runner_iter;
		}
		
		runner_iter = DLLNext(runner_iter);
	}
	
	return NULL;
}

int HTForEach(ht_t *ht, ht_action_func_t act, void *action_param)
{
	int status = SUCCESS;
	size_t i = 0;
	
	assert(NULL != ht);
	assert(NULL != act);
	
	for(i = 0; (i < ht->entries) && (SUCCESS == status); ++i)
	{
		status = DLLForEach(act, action_param,
				 			DLLBegin(ht->buckets[i]), DLLEnd(ht->buckets[i]));
	}
	
	return status;
}


static size_t GetBucketIndex(ht_t *ht, void *data)
{
	return ht->ht_func(data, ht->ht_param) % ht->entries;
}


