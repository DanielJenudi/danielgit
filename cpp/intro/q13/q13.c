#include <stdio.h> /* printf */

void DoStuff();

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo() { printf("useless\n"); }

    namespace wasteoftyme
    {
        void Foo() { printf("useless2\n"); }
    } // namespace wasteoftyme
} // namespace useless

int main()
{
    using namespace useless;

    Foo();
    wasteoftyme::Foo();

    DoStuff();

    return 0;
}

namespace stupid
{
    void Foo() { printf("stupid\n"); }
    void Bar() {}
    void DoNothing(unsigned int) {}
} // namespace stupid

namespace useless
{
    void DoNothing(int) {}
} // namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {}
using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    // Foo(); //try uncommenting this line, solve the error
    Bar(); // why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
} // namespace useless