#include <iostream>

struct X
{
    X(int a_, int b_);

    void Inccccccccccccccccccccccc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
}

void X::Inccccccccccccccccccccccc()
{
    ++m_a;
    ++m_b;
    std::cout << "this:" << this << std::endl;
}

void X::Dec()
{
    --m_a;
    --m_b;
    std::cout << "this:" << this << std::endl;
}

void Inccccccccccccccccccccccc()
{
}

int main()
{
    X x1(7, -55);
    X x2(x1);

    Inccccccccccccccccccccccc();
    x1.Inccccccccccccccccccccccc();

    std::cout << "x1.m_a:" << x1.m_a << " x1.m_b:" << x1.m_b << std::endl;
    x1.Inccccccccccccccccccccccc();
    std::cout << "x1.m_a:" << x1.m_a << " x1.m_b:" << x1.m_b << std::endl;
    x2.Dec();
    std::cout << "x2.m_a:" << x2.m_a << " x2.m_b:" << x2.m_b << std::endl;

    return 0;
}