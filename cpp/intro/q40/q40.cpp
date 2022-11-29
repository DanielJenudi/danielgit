#include <iostream>

class X
{
public:
    virtual ~X() { std::cout << "Dtor X" << std::endl; }

private:
    int m_a;
};

class Y : public X
{
public:
    virtual ~Y() { std::cout << "Dtor Y" << std::endl; }

private:
    int m_b;
};

void Foo(X x)
{
}

int main()
{
    /* X *xp = new Y[5]; */
    Y y1;

    Foo(y1);

    /* delete[] xp; */

    return 0;
}
