#include <cstddef>  // size_t
#include <iostream> // cout

#define FAIL (0xffffffffffffffff)

size_t MinCoin(size_t *arr, size_t size, size_t target);
static size_t ReqFunc(size_t *arr, long size, size_t target,
                      size_t cur_sum, size_t counter);

int main()
{
    size_t arr[] = {1, 4, 5};

    std::cout << MinCoin(arr, sizeof(arr) / sizeof(size_t), 8) << std::endl;

    return 0;
}

size_t MinCoin(size_t *arr, size_t size, size_t target)
{
    size_t min = 0xffffffffffffffff;

    for (size_t i = 1; i <= size; ++i)
    {
        size_t temp_res = ReqFunc(arr, size - i, target, 0, 0);
        if (min > temp_res)
        {
            min = temp_res;
        }
    }

    return min;
}

static size_t ReqFunc(size_t *arr, long max_index, size_t target,
                      size_t cur_sum, size_t counter)
{
    if (cur_sum == target)
    {
        return counter;
    }

    while (((arr[max_index] + cur_sum) > target) && (0 <= max_index))
    {
        --max_index;
    }

    while (0 <= max_index)
    {
        size_t result = ReqFunc(arr, max_index, target,
                                cur_sum + arr[max_index], counter + 1);

        if (FAIL != result)
        {
            return result;
        }
        --max_index;
    }

    return FAIL;
}