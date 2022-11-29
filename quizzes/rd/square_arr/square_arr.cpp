#include <cstddef>  // size_t
#include <cstring>  // memcpy
#include <iostream> // cout

void Sorted_Square(int *arr, size_t size);

static size_t AbsoluteValue(int num);
static void PrintArr(int *arr, size_t size);

int main()
{
    int arr1[] = {-10, -1, 5, 6};

    std::cout << "Test 1" << std::endl;
    Sorted_Square(arr1, sizeof(arr1) / sizeof(int));
    PrintArr(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = {-10, -6, -5, -1};

    std::cout << "Test 2:" << std::endl;
    Sorted_Square(arr2, sizeof(arr2) / sizeof(int));
    PrintArr(arr2, sizeof(arr2) / sizeof(int));

    int arr3[] = {-1, -1, 0, 5, 6};

    std::cout << "Test 3" << std::endl;
    Sorted_Square(arr3, sizeof(arr3) / sizeof(int));
    PrintArr(arr3, sizeof(arr3) / sizeof(int));

    int arr4[] = {-100, -50, -3, -1, 0, 1, 2, 10, 30, 70};

    std::cout << "Test 4" << std::endl;
    Sorted_Square(arr4, sizeof(arr4) / sizeof(int));
    PrintArr(arr4, sizeof(arr4) / sizeof(int));

    return 0;
}

void Sorted_Square(int *arr, size_t size)
{
    size_t pos_index = size - 1;
    size_t neg_index = 0;

    int *result = new int[size];
    int *result_runner = result;

    while (pos_index > neg_index)
    {
        size_t neg_absoiute = AbsoluteValue(arr[neg_index]);

        if (static_cast<int>(neg_absoiute) > arr[pos_index])
        {
            *result_runner = neg_absoiute * neg_absoiute;
            ++neg_index;
        }
        else
        {
            *result_runner = arr[pos_index] * arr[pos_index];
            --pos_index;
        }

        ++result_runner;
    }

    memcpy(arr, result, sizeof(int) * size);

    delete[] result;
    result = 0;
}

static size_t AbsoluteValue(int num)
{
    if (0 > num)
    {

        return -num;
    }
    else
    {
        return num;
    }
}

static void PrintArr(int *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << "  ";
    }

    std::cout << std::endl;
}
