#include <iostream> // cout
#include <dlfcn.h>  // dlopen

#include "singleton.hpp"
#include "ex1.hpp"

using namespace std;
using namespace ilrd;

using int_func_t = void (*)();

int main()
{
    void *handle = dlopen("./libex1.so", RTLD_LAZY);
    if (0 == handle)
    {
        perror("fail to open\n");
        return 0;
    }

    int_func_t get_singleton_func = 0;
    *(void **)(&get_singleton_func) = dlsym(handle, "_Z3Getv");
    if (0 == get_singleton_func)
    {
        perror("fail to find func\n");
        return 0;
    }
    (*get_singleton_func)();

    dlclose(handle);

    // Get();

    return 0;
}