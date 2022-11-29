/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 14/08/22
- Reviewed By: Moshe Schreiber
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream> // cout

#include "reg_file.hpp"

namespace ilrd
{
    Reg_File::Reg_File(const std::string &name) : m_name(name)
    {
        // empty
    }

    Reg_File::~Reg_File() noexcept
    {
        m_name.clear();
    }

    void Reg_File::print(size_t indents)
    {
        for (size_t i = 0; i < indents; ++i)
        {
            std::cout << " ";
        }

        std::cout << m_name << std::endl;
    }
}
