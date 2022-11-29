#include <iostream>
#include <set>

#include "singleton.hpp"

using namespace ilrd;
using namespace std;

void Get(void)
{
    cout << "dynamic :" << Singleton<int>::GetInstance() << endl;
}