#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

struct BadDog : public runtime_error
{
    BadDog(const string &s_ = "This is a bad dog") : runtime_error(s_) {}
    ~BadDog() throw() { std::cout << "BadDog::Dtor" << std::endl; }
};

class X
{
public:
    X() { std::cout << "X::Ctor" << std::endl; }
    ~X() { std::cout << "X::Dtor" << std::endl; }

private:
    int m_a;
};

void Fifi()
{
    throw BadDog("bad pup\n");
    cerr << "Fifi() after throw" << endl;
}
void Foo()

{
    X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}
int main()
{
    try
    {
        Bar();
    }
    catch (bad_alloc &)
    {
        cerr << "Out of memory! exiting.";
        exit(2);
    }
    catch (BadDog &b)
    {
        cerr << "Bad dog exception: " << b.what();
        exit(3);
    }
    catch (exception &r)
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }

    cerr << "hello" << endl;

    return 0;
}