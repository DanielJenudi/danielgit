#include <iostream>

enum range
{
    LOW = 0,
    HIGHT = 1
};

void FindMissing(const int *arr, size_t len, const int *range);

int main()
{
    int arr[] = {2, 5, 7, 10, 12, 13};
    int range[] = {2, 13};

    FindMissing(arr, 6, range);

    return 0;
}

void FindMissing(const int *arr, size_t len, const int *range)
{
    int limit = 0;
    int runner = range[LOW];

    for (size_t i = 0; i < len; ++i)
    {
        limit = arr[i];

        while (runner < limit)
        {
            std::cout << runner << std::endl;
            ++runner;
        }
        ++runner;
    }

    limit = range[HIGHT];

    while (runner < (limit + 1))
    {
        std::cout << runner << std::endl;
        ++runner;
    }
}