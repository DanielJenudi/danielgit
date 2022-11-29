#include <iostream>

#include "q16.h"

int BLA()
{
    int arr[12];

    for (size_t i = 0; i < 12; ++i)
    {
        arr[i] = i;
    }

    std::cout << Max<int>(3, 5) << "\n"
              << Max<double>(3.7, 12.9) << std::endl;
    std::cout << *(Max<int *>(arr, arr + 8)) << std::endl;
    std::cout << Max<char>('a', 'b') << std::endl;

    return 0;
}
