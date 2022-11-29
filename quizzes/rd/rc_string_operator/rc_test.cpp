#include <iostream> // cout

#include "rc.hpp"

using namespace ilrd;

int main()
{

    String s1("hello");
    String s2("world");

    std::cout << "before:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;
    std::cout << "s2 = " << s2.GetStr() << std::endl;

    s1 = s2;
    s1 = "aaa";

    std::cout << "\nafter:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;
    std::cout << "s2 = " << s2.GetStr() << std::endl;

    s1 = "daniel";

    std::cout << "\nstring literal:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;

    return 0;
}
