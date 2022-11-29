#include <dlfcn.h>   // dllopen, dllclose, dllsym
#include <stdexcept> // runtime_error

#include <iostream>

#include "dll_loader.hpp"

namespace ilrd
{

    DllLoader::DllLoader()
    {
        // empty
    }

    DllLoader::~DllLoader()
    {
        for (auto i = m_dll_names.begin(); i != m_dll_names.end(); ++i)
        {
            dlclose(*i);
        }
    }

    void DllLoader::AddDll(std::string dll_name)
    {

        void *handle = dlopen(dll_name.c_str(), RTLD_NOW);
        std::cout << "opend\n";
        if (nullptr == handle)
        {
            throw std::runtime_error(dlerror());
        }

        m_dll_names.push_back(handle);
    }
}