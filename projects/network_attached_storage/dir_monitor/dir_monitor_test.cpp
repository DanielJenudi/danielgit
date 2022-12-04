#include <string>
#include <iostream>

#include "dir_monitor.hpp"
#include "dll_loader.hpp"

using namespace ilrd;

static void Add(std::string str)
{
    DllLoader dll_loader;
    dll_loader.AddDll(str);
}

int main()
{
    DirMonitor dir_monitor("./lib", Add);
    dir_monitor.Run();

    std::cout << "eyad is bulling me\n";
    std::cout << "eyad is bulling me\n";
    std::cout << "eyad is bulling me\n";

    return 0;
}