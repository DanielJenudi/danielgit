#include <stddef.h>/* size_t */
#include <stdio.h>/* printf */
#include <assert.h>/* assert */

enum
{
    SUCCESS = 0,
    FAIL = -1
}

int FindDivider(int *arr, size_t size);

int main()
{
    int arr1[] = {1, 1, 2, 3, 4};
    int arr2[] = {9, 3, 3, 6};
    int arr3[] = {9, 3, 3, 1};


    printf("arr1: %d\n", FindDivider(arr1, 5));
    printf("arr2: %d\n", FindDivider(arr2, 4));
    printf("arr3: %d\n", FindDivider(arr3, 4));

    return SUCCESS;
}

int FindDivider(int *arr, size_t size)
{
    int *start = NULL;
    int *end = NULL;
    long sum_s = 0;
    long sum_e = 0;

    assert(NULL != arr);
    
    start = arr;
    end = arr + (size - 1);

    while(1 < size)
    {
        if(sum_s > sum_e)
        {
            sum_e += *end;
            --end;
        }
        else
        {
            sum_s += *start;
            ++start;
        }

        --size;
    }

    if(sum_s == sum_e)
    {
        return (start - arr);
    }
    else
    {
        return FAIL;
    }
}

