/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer:
 *Date: 15.09.22
 ******************************************************************************/

#include "singleton.hpp"
#include <iostream>

using namespace ilrd;

int main()
{
    int *a = Singleton<int>::GetInstance();
    int *b = Singleton<int>::GetInstance();
    int *c = Singleton<int>::GetInstance();

    *a = 1;

    std::cout << *a << std::endl;
    std::cout << *b << std::endl;
    std::cout << *c << std::endl;

    std::cout << std::endl;

    *b = 2;

    std::cout << *a << std::endl;
    std::cout << *b << std::endl;
    std::cout << *c << std::endl;

    std::cout << std::endl;

    *c = 3;

    std::cout << *a << std::endl;
    std::cout << *b << std::endl;
    std::cout << *c << std::endl;

    return 0;
}