#include <cstring>  // memcpy
#include <new>      // operator new, operator delete
#include <iostream> // cout

using namespace std;

void MergSort(int *arr, size_t size);
void PrintArr(int *arr, size_t size);

int main()
{
    int arr[] = {2, 5, 6, 1, 77, 8, 23, 0, -33, -2, 10, 12, -100};
    size_t size = sizeof(arr) / sizeof(int);

    MergSort(arr, size);
    PrintArr(arr, size);

    return 0;
}

void PrintArr(int *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << "index " << i << ": " << arr[i] << std::endl;
    }
}
void MergSort(int *arr, size_t size)
{
    if (1 >= size)
    {
        return;
    }

    size_t sec_half_size = size / 2;
    size_t first_half_size = size - sec_half_size;

    MergSort(arr, first_half_size);
    MergSort(arr + first_half_size, sec_half_size);

    int *temp_arr = (int *)operator new(sizeof(int) * size);

    size_t run1 = 0;
    size_t run2 = run1 + first_half_size;
    size_t result_runner = 0;

    while ((run1 != first_half_size) && (run2 != size))
    {
        if (arr[run1] > arr[run2])
        {
            temp_arr[result_runner] = arr[run1];
            ++run1;
        }
        else
        {
            temp_arr[result_runner] = arr[run2];
            ++run2;
        }

        ++result_runner;
    }

    while (run1 != first_half_size)
    {
        temp_arr[result_runner] = arr[run1];
        ++run1;
        ++result_runner;
    }

    while (run2 != size)
    {
        temp_arr[result_runner] = arr[run2];
        ++run2;
        ++result_runner;
    }

    memcpy(arr, temp_arr, size * sizeof(int));

    operator delete(temp_arr);
    temp_arr = 0;
}
