#include <cstdio>

class X
{
public:
    explicit X();
    explicit X(int a_);
    void Foo();
    int Ret_m_a() const;

private:
    int m_a;
};

X::X(int a_) : m_a(a_)
{
}

X::X() : m_a(10)
{
}

int X::Ret_m_a() const
{
    return m_a;
}

void X::Foo()
{
    printf("%d\n", m_a);
}

void Foo(const X &x_)
{
    printf("%d\n", x_.Ret_m_a());
}

int main()
{
    X x1;

    x1.Foo();
    printf("%d\n", x1.Ret_m_a());
    Foo(x1);

    return 0;
}