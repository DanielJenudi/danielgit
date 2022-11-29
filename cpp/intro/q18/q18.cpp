#include <iostream>

void PrintA(double &ip);
void PrintB(double ip);

int main()
{
    double i = 8;
    char c = 'a';
    double &ip = i;
    char &cp = c;

    i = 9.43;

    PrintA(i);

    std::cout << ip << std::endl;

    PrintB(ip);

    std::cout << ip << std::endl;

    std::cout << sizeof(ip) << std::endl;
    std::cout << sizeof(cp) << std::endl;

    return 0;
}

void PrintA(double &ip)
{
    std::cout << ip << std::endl;

    ip = 5;
}

void PrintB(double ip)
{
    std::cout << ip << std::endl;

    ip = 6;
}
