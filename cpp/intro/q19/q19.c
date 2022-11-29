#include <iostream>

void PrintA(double &ip);
void PrintB(const double &ip);

int main()
{
    int i = 5;

    std::cout << i << " " << &i << std::endl;

    PrintA(i);

    PrintB(i);

    return 0;
}

void PrintA(double &ip)
{
    std::cout << &ip << std::endl;
}

void PrintB(const double &ip)
{
    std::cout << ip << " " << &ip << std::endl;
}
