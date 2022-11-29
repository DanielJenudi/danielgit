#include <cstddef>  // size_t
#include <iostream> // cout

size_t MaxConsective(int *arr, size_t size, size_t N);

int main()
{
    int arr1[] = {1, 0, 0, 1, 1};

    std::cout << "arr1: " << MaxConsective(arr1, sizeof(arr1) / sizeof(int), 1)
              << " need to be: 3" << std::endl;

    int arr2[] = {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0};

    std::cout << "arr2: " << MaxConsective(arr2, sizeof(arr2) / sizeof(int), 2)
              << " need to be: 6" << std::endl;

    int arr3[] = {1, 0, 0, 1, 1};

    std::cout << "arr3: " << MaxConsective(arr3, sizeof(arr3) / sizeof(int), 0)
              << " need to be: 2" << std::endl;

    int arr4[] = {1, 0, 0, 1, 1};

    std::cout << "arr4: " << MaxConsective(arr4, sizeof(arr4) / sizeof(int), 7)
              << " need to be: 5" << std::endl;

    int arr5[] = {1, 0, 1, 0, 1, 0, 1, 0, 1};

    std::cout << "arr5: " << MaxConsective(arr5, sizeof(arr5) / sizeof(int), 2)
              << " need to be: 5" << std::endl;

    int arr6[] = {1, 0, 0, 1, 1, 1, 0, 0, 1, 1};

    std::cout << "arr6: " << MaxConsective(arr6, sizeof(arr6) / sizeof(int), 2)
              << " need to be: 7" << std::endl;

    int arr7[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::cout << "arr7: " << MaxConsective(arr7, sizeof(arr7) / sizeof(int), 3)
              << " need to be: 3" << std::endl;
}

size_t MaxConsective(int *arr, size_t size, size_t N)
{
    size_t cur_n = N, counter = 0, max_counter = 0;
    int *runner = arr;
    int *end = arr + (size - 1);
    int *next_one = end;

    if (size <= N)
    {
        return size;
    }

    while (end >= runner)
    {
        if (1 == *runner)
        {
            ++counter;
            ++runner;
        }
        else if (0 != cur_n)
        {
            if (N == cur_n)
            {
                next_one = runner;
                while ((1 != *next_one) && (end > next_one))
                {
                    ++next_one;
                }
            }

            ++counter;
            ++runner;
            --cur_n;
        }
        else
        {
            max_counter = max_counter > counter ? max_counter : counter;

            if (0 != N)
            {
                runner = next_one;
            }
            else
            {
                while ((1 != *runner) && (end > runner))
                {
                    ++runner;
                }
            }

            cur_n = N;
            counter = 0;
        }
    }

    return max_counter > (counter + cur_n) ? max_counter : (counter + cur_n);
}
