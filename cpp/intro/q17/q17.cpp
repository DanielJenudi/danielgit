#include <iostream>
#include <typeinfo>

template <typename T>
void foooooooooooooooooooooo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

void foooooooooooooooooooooo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

int main()
{
    foooooooooooooooooooooo(4.2);
    foooooooooooooooooooooo(5);
    foooooooooooooooooooooo<int>(5);

    return 0;
}