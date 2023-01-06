#include <iostream> //cout

#include "rc_str.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    RC_STR rc_str1;
    RC_STR rc_str2("hello");
    RC_STR rc_str3("daniel");
    RC_STR rc_str4(rc_str3);

    rc_str4 = "jenudi";

    cout << rc_str1 << endl;
    cout << rc_str2 << endl;
    cout << rc_str3 << endl;
    cout << rc_str4 << endl;
    cout << endl;

    rc_str1 = rc_str2;

    cout << rc_str1 << endl;
    cout << rc_str2 << endl;
    cout << rc_str3 << endl;
    cout << rc_str4 << endl;
    cout << endl;

    rc_str3 = rc_str2;

    cout << rc_str1 << endl;
    cout << rc_str2 << endl;
    cout << rc_str3 << endl;
    cout << rc_str4 << endl;
    cout << endl;

    rc_str1 = rc_str4;
    rc_str2 = rc_str4;
    rc_str3 = rc_str4;

    cout << rc_str1 << endl;
    cout << rc_str2 << endl;
    cout << rc_str3 << endl;
    cout << rc_str4 << endl;
    cout << endl;
}