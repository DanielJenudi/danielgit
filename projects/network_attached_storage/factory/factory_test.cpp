/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Nuriel Hamo
 *Date: 14/09/2022
 *****************************************************************************/

#include <iostream>
#include "factory.hpp"

using namespace std;
using namespace ilrd;

class args
{
public:
    args(int y = 1) : x(y) {}
    int x;
};

class base
{
public:
    virtual void print() = 0;
    virtual ~base() {}
};
class derived : public base
{
public:
    derived(int y = 3) : x(y) {}
    virtual void print() { cout << "derived\n"; }

    int x;
};
class derived1 : public base
{
public:
    derived1(int y = 2) : x(y) {}
    virtual void print() { cout << "derived 1\n"; }

    int x;
};
class derived2 : public base
{
public:
    derived2(args a) : x(a.x) {}
    virtual void print() { cout << "derived 2\n"; }

    int x;
};

base *CreateDerived(const args &a)
{
    (void)(a);
    return new derived();
}
base *CreateDerived1(const args &a)
{
    (void)(a);
    return new derived1();
}
base *CreateDerived2(const args &a)
{
    return new derived2(a);
}

int main()
{
    Factory<base, unsigned int, args> f;
    f.Add(0, CreateDerived);
    f.Add(1, CreateDerived1);
    f.Add(2, CreateDerived2);

    base *a = f.Create(0, args());
    base *b = f.Create(1, args());
    base *c = f.Create(2, args());
    a->print();
    b->print();
    c->print();

    try
    {
        f.Add(0, CreateDerived);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        f.Create(4, args());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    delete a;
    delete b;
    delete c;

    return 0;
}