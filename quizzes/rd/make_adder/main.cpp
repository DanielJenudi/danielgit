#include <iostream> // cout

using namespace std;

class make_adder
{
public:
    make_adder(int);
    int operator()(int);

private:
    int m_num;
};

make_adder::make_adder(int num) : m_num(num)
{
    // empty
}

int make_adder::operator()(int num)
{
    return num + m_num;
}

int main()
{
    make_adder add_4 = make_adder(4);

    cout << add_4(5) << endl;
    cout << add_4(8) << endl;

    return 0;
}
