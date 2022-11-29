#include <iostream>
#include "tricky_string.hpp"

using namespace ilrd;

int main()
{
    String s1("1234");
    std::cout << s1 << std::endl;
    s1 = '@'; // will change s1 to "@@@@"
    std::cout << s1 << std::endl;
    String *s2 = new String;
    std::cout << s2->Cstr() << std::endl;
    std::cout << s2->GetInstances() << std::endl; // will print 2
    delete s2;
    std::cout << String::GetInstances() << std::endl; // will print 1
}