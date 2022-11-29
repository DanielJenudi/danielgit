#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

enum result
{
    START = 0,
    END,
    SUM
};

void FindMaxSubArray(int *arr, size_t size, int *result);

int main()
{
    int arr[] = {-1, 3, -2, 5, -6, 7, -8, 1, 1, 1, -10};
    int result[3] = {0};

    FindMaxSubArray(arr, (sizeof(arr) / sizeof(int)), result);

    printf("start: %d\n", result[START]);
    printf("end: %d\n", result[END]);
    printf("sum: %d\n", result[SUM]);

    return 0;
}

void FindMaxSubArray(int *arr, size_t size, int *result)
{
    int cur[3] = {0};

    assert(NULL != arr);
    assert(NULL != result);
    assert(0 != size);

    result[START] = 0;
    result[END] = 0;
    result[SUM] = arr[0];

    cur[SUM] = arr[0];

    while (1 != size)
    {
        ++cur[END];
        if (0 > (cur[SUM] + arr[cur[END]]) || (0 > arr[cur[START]]))
        {
            cur[START] = cur[END];
            cur[SUM] = arr[cur[END]];
        }
        else
        {
            cur[SUM] += arr[cur[END]];
        }

        if (result[SUM] < cur[SUM])
        {
            result[START] = cur[START];
            result[END] = cur[END];
            result[SUM] = cur[SUM];
        }

        --size;
    }
}
