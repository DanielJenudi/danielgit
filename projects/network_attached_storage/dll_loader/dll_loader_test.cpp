#include "dll_loader.hpp"

using namespace ilrd;

int main()
{
    DllLoader dll_loader;

    dll_loader.AddDll("./libshapes.so");

    return 0;
}