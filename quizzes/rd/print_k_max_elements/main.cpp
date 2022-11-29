
#include <bits/stdc++.h> //INT_MIN
#include <iostream>      // cout

void PrintMaxElement(int *arr, size_t size, size_t k);
static void PutInMaxArr(int *arr, size_t size, int num);
static void PrintArr(int *arr, size_t size);

using namespace std;

int main()
{
    int arr[] = {2, 4, 5, 1, 7, 6};
    size_t size = sizeof(arr) / sizeof(int);

    PrintMaxElement(arr, size, 3);

    return 0;
}

void PrintMaxElement(int *arr, size_t size, size_t k)
{
    if ((0 == size) || (k == 0))
    {
        return;
    }

    k = size < k ? size : k;

    int *max_arr = new int[k];
    memset(max_arr, INT_MIN, k);

    for (size_t i = 0; i < size; ++i)
    {
        PutInMaxArr(max_arr, k, arr[i]);
    }

    PrintArr(max_arr, k);

    delete[] max_arr;
    max_arr = 0;
}

static void PutInMaxArr(int *arr, size_t size, int num)
{
    if (num > arr[0])
    {
        for (size_t i = 1; i < size; ++i)
        {
            if (arr[i] < num)
            {
                arr[i - 1] = arr[i];
                arr[i] = num;
            }
            else
            {
                arr[i - 1] = num;
                break;
            }
        }
    }
}

static void PrintArr(int *arr, size_t size)
{
    for (size_t i = (size - 1); (0 != i); --i)
    {
        std::cout << "max " << i << ": " << arr[i] << std::endl;
    }

    std::cout << "max 0: " << arr[0] << std::endl;
}