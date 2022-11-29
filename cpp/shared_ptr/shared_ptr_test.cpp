/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Hagar
 *Date: 01.09.22
 ******************************************************************************/

#include <string>   // string
#include <iostream> // cout
#include <cstring>

#include "shared_ptr.hpp"

using namespace ilrd;
using namespace std;

class base1
{
};
class derived1 : public base1
{
};
class base2
{
};
class derived2
{
};

int main()
{
    Shared_Pointer<int> s_int1(new int(5));
    Shared_Pointer<int> s_int2(new int(7));

    Shared_Pointer<double> s_double(new double(9.4));
    Shared_Pointer<string> s_string(new string("hello"));

    std::cout << *s_int1.GetPtr() << std::endl;
    std::cout << *s_int2.GetPtr() << std::endl;
    std::cout << *s_double.GetPtr() << std::endl;
    std::cout << *s_string.GetPtr() << std::endl;

    bool bo = (s_int1 == s_int2);
    std::cout << bo << std::endl;

    s_int1 = s_int2;
    std::cout << *s_int2.GetPtr() << std::endl;

    bo = (s_int1 == s_int2);
    std::cout << bo << std::endl;

    string *str = new string("blabla");
    Shared_Pointer<base1> b(new base1());
    Shared_Pointer<base1> b1(new derived1());
    Shared_Pointer<derived1> d1(new derived1());
    Shared_Pointer<derived1> d3(new derived1());
    Shared_Pointer<base2> b2(new base2());
    Shared_Pointer<derived2> d2(new derived2());
    Shared_Pointer<std::string> s(str);
    Shared_Pointer<base1> b4 = d1;

    cout << s->c_str() << endl;
    cout << (*s).c_str() << endl;
    b1 = d1;

    b1 = d1 = d3;

    return 0;
}