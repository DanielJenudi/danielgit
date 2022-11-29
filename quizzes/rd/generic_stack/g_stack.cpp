#include <iostream> // cout

#include "g_stack.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    Generic_stack<int> s1;

    s1.Push(5);
    s1.Push(6);
    s1.Push(7);

    cout << "empty: " << s1.Empty() << endl;
    cout << "size: " << s1.Size() << endl;

    cout << "peek: " << s1.Peek() << endl;

    cout << "pop: " << s1.Pop() << endl;
    cout << "pop: " << s1.Pop() << endl;
    cout << "pop: " << s1.Pop() << endl;

    cout << "empty: " << s1.Empty() << endl;

    return 0;
}