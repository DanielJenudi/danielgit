/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 25/05/2022
File: Data Structures - Heap
Description: Implementing heap data structure
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h>/* malloc, free */
#include <assert.h>/* assert */
#include <stdio.h>

#include "d_vector.h"
#include "heap.h"

#define START_CAPACITY (10)
#define ROOT_INDEX (0)
#define LAST_INDEX (HeapSize(heap) - 1)
#define FATHER_INDEX(child) ((((child) - 1) / 2) * (!!child))
#define CHILD_LEFT_INDEX(father) (((father) * 2) + 1)
#define CHILD_RIGHT_INDEX(father) (((father) * 2) + 2)

enum Status
{
    SUCCESS = 0,
    FALSE = 0,
    TRUE = 1,
    FAIL
};

struct heap
{
	d_vector_t *heap;
	heap_cmp_func_t cmp;
	void *cmp_param;
};

static void HeapifyUp(heap_t *heap, size_t child_index);
static void HeapifyDown(heap_t *heap, size_t parent_index);
static void SwapData(void **data1, void **data2);

heap_t *HeapCreate(heap_cmp_func_t cmp, void *cmp_param)
{
    heap_t *heap = NULL;

    assert(NULL != cmp);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if(NULL == heap)
    {
        return NULL;
    }

    heap->heap = VectorCreate(sizeof(size_t), START_CAPACITY);
    if(NULL == heap->heap)
    {
        free(heap);
        heap = NULL;

        return NULL;
    }

    /*init heap*/
    heap->cmp = cmp;
    heap->cmp_param = cmp_param;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->heap);
    heap->heap = NULL;

    free(heap);
    heap = NULL;
}

void *HeapPeek(heap_t *heap)
{
    assert(NULL != heap);
    assert(FALSE == HeapIsEmpty(heap));
  
    return *(void **)VectorGetElement(heap->heap, ROOT_INDEX);
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->heap);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorIsEmpty(heap->heap);
}

int HeapPush(heap_t *heap, void *new_data)
{
    assert(NULL != heap);

    if(FAIL == VectorPushBack(heap->heap, &new_data))
    {
        return FAIL;
    }

    HeapifyUp(heap, LAST_INDEX);

    return SUCCESS;
}

static void HeapifyUp(heap_t *heap, size_t child_index)
{
    size_t parent_index = FATHER_INDEX(child_index);
    void **parent = NULL;
    void **child = NULL;

    assert(NULL != heap);

    if(0 != child_index)
    {
        parent = VectorGetElement(heap->heap, parent_index);
        child = VectorGetElement(heap->heap, child_index);

        if(0 < heap->cmp(*child, *parent, heap->cmp_param))
        {
            SwapData(parent, child);
            HeapifyUp(heap, parent_index);
        }
    }
}

void *HeapPop(heap_t *heap)
{
    void *pop_return = NULL;
    void **start = NULL;
    void **last = NULL;

    assert(NULL != heap);
    assert(FALSE == HeapIsEmpty(heap));

    last = VectorGetElement(heap->heap, LAST_INDEX);
    start = VectorGetElement(heap->heap, ROOT_INDEX);

    pop_return = *start;

    SwapData(start, last);
    VectorPopBack(heap->heap);
    HeapifyDown(heap, ROOT_INDEX);

    return pop_return;
}

static void HeapifyDown(heap_t *heap, size_t parent_index)
{
    size_t left_index = CHILD_LEFT_INDEX(parent_index);
    size_t right_index = CHILD_RIGHT_INDEX(parent_index);
    size_t vector_size = 0; 
    void *left_child = NULL;
    void *right_child = NULL;
    void *parent = NULL;

    assert(NULL != heap);

    vector_size = VectorSize(heap->heap);
    parent = VectorGetElement(heap->heap, parent_index);

    if (left_index < vector_size && right_index < vector_size)
    {
        left_child = VectorGetElement(heap->heap, left_index);
        right_child = VectorGetElement(heap->heap, right_index);

        if(0 < heap->cmp(*(void **)left_child, *(void **)right_child, 
                         heap->cmp_param))
        {
            if(0 < heap->cmp(*(void **)left_child, *(void **)parent, 
                         heap->cmp_param))
            {
                SwapData(parent, left_child);
                HeapifyDown(heap, left_index);
            }
        }
        else
        {
            if(0 < heap->cmp(*(void **)right_child, *(void **)parent, 
                         heap->cmp_param))
            {
                SwapData(parent, right_child);
                HeapifyDown(heap, right_index);
            }
        }   
    }
    else if (left_index < vector_size)
    {
        left_child = VectorGetElement(heap->heap, left_index);
        if(0 < heap->cmp(*(void **)left_child, *(void **)parent, 
                         heap->cmp_param))
        {
            SwapData(parent, left_child);
            HeapifyDown(heap, left_index);
        }
    }
}

static void SwapData(void **data1, void **data2)
{
    void *temp = NULL;

    assert(NULL != data1);
    assert(NULL != data2);    

    temp = *data1;
    *data1 = *data2;
    *data2 = temp;  
}

void *HeapRemove(heap_t *heap, void *to_remove, 
				is_match_t match_func, void *match_param)
{
    size_t check_index = 0;
    size_t heap_size = 0;
    void *check = NULL;
    void *remove_return = NULL;
    void *last = NULL;

    assert(NULL != heap);
    assert(NULL != match_func);
    
    heap_size = VectorSize(heap->heap);

    while ((check_index <  heap_size) && (NULL == remove_return))
    {
        check = VectorGetElement(heap->heap, check_index);

        if(TRUE == match_func(to_remove, *(void **)check, match_param))
        {
            remove_return = *(void **)check;
            last = VectorGetElement(heap->heap, LAST_INDEX);

            SwapData(check, last);
            VectorPopBack(heap->heap);

            HeapifyUp(heap, check_index);
            HeapifyDown(heap, check_index);
        }
        ++check_index;
    } 

    return remove_return;
}

void PrintTree(heap_t *heap)
{
    size_t i = 0;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(i = 0; i < HeapSize(heap); ++i)
    {
        printf("%d ", **(int **)VectorGetElement(heap->heap, i));
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}