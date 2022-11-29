#include <iostream>

class X
{
public:
    X(double d_) : m_a(d_) {}
    virtual ~X() { std::cout << "Dtor X" << std::endl; }

    // private:
    double m_a;
};

class Y : public X
{
public:
    Y(double d_, int i_) : X(d_), m_b(i_) {}
    virtual ~Y() { std::cout << "Dtor Y" << std::endl; }

    // private:
    int m_b;
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    std::cout << "x1: " << x1.m_a << std::endl;
    std::cout << "x2: " << x2.m_a << std::endl;

    std::cout << "y1: " << y1.m_b << std::endl;
    std::cout << "y2: " << y2.m_b << std::endl
              << std::endl;

    x1 = x2;
    y3 = y4;

    std::cout << "x1: " << x1.m_a << std::endl;
    std::cout << "x2: " << x2.m_a << std::endl;

    std::cout << "y1: " << y1.m_b << std::endl;
    std::cout << "y2: " << y2.m_b << std::endl
              << std::endl;

    std::cout << "y3 m_a: " << y3.m_a << std::endl;
    std::cout << "y3 m_b: " << y3.m_b << std::endl;
    std::cout << "y4 m_a: " << y4.m_a << std::endl;
    std::cout << "y4 m_b: " << y4.m_b << std::endl;

    return 0;
}