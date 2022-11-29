#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <new>
#include <typeinfo>

using namespace std;

int Foo(int a) throw(bad_alloc)
{
    cout << a << " "
         << "im Foo" << endl;
    throw bad_alloc();
}

class X
{
public:
    X()
    {
        cout << "im X" << endl;
    }

    ~X()
    {
        cout << "de-initializing X" << endl;

        cerr << Foo(m_a) << endl;
        /*     try
            {
                cerr << Foo(m_a) << endl;
            }
            catch (exception &e)
            {
                cout << "error";
            } */
    }

private:
    int m_a;
};

void Bar() throw(bad_cast)
{
    throw bad_cast();
}

void Fishi()
{
    X x1;
    Bar();
}

int main()
{
    try
    {
        Fishi();
    }

    catch (bad_alloc &)
    {
        cerr << "Out of memory! exiting.";
        exit(2);
    }

    catch (bad_cast &)
    {
        cerr << "Bad cast! exiting.";
        exit(3);
    }

    return 0;
}