#include <iostream>
#include "simple_string.hpp"

using namespace ilrd;

int main()
{
    String s1("hello");
    String s2(s1);
    String s3("world");

    std::cout << s1.Length() << std::endl;
    std::cout << s1.Cstr() << " " << s3.Cstr() << std::endl;

    std::cout << " >> operator:" << std::endl;
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;

    std::cout << "s1 == s2 -> ";
    std::cout << (s1 == s2) << std::endl;

    std::cout << "hello == s1; -> ";
    std::cout << ("hello" == s1) << std::endl;

    std::cout << "123 == s1; -> ";
    std::cout << ("123" == s1) << std::endl;

    std::cout << "s1 > s3 -> ";
    std::cout << (s1 > s3) << std::endl;

    std::cout << "s1 < s3 -> ";
    std::cout << (s1 < s3) << std::endl;

    const char *ss1 = "hello";
    const char *ss2 = "hi";
    std::cout << "ss1 == ss2 -> ";
    std::cout << (ss1 == ss2) << std::endl;

    return 0;
}