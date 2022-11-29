#include <stdio.h>
#include "foo.h"
#include <dlfcn.h>

int main(void)
{
    void *handle;
	void (*foo)(void);

    puts("This is a shared library test...");
    handle = dlopen("/home/daniel/git/system_programming/libraries/libfoo.so",
    RTLD_LOCAL | RTLD_LAZY);
    *(void**)&foo = dlsym(handle, "foo"); 
    foo();
    dlclose(handle);

	return 0;
}

