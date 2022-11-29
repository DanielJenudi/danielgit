#include <cstddef> // size_t
#include <cstring> // strlen, memcpy

#include "rc.hpp"

namespace ilrd
{

    String::String(const char *str) : m_rc(new RC)
    {
        size_t len = strlen(str) + 1;
        m_rc->m_str = new char[len];

        memcpy(m_rc->m_str, str, len);
        m_rc->m_count = 1;
    }

    String::~String()
    {
        if (m_rc->m_count > 1)
        {
            --m_rc->m_count;
        }
        else
        {

            delete[] m_rc->m_str;
            m_rc->m_str = 0;
            delete m_rc;
            m_rc = 0;
        }
    }

    String &String::operator=(const String &other)
    {
        if (this != &other)
        {
            this->~String();

            m_rc = other.m_rc;
            ++m_rc->m_count;
        }

        return *this;
    }

    String &String ::operator=(const char *str)
    {
        *this = String(str);

        return *this;
    }

    char *String::GetStr() const
    {
        return m_rc->m_str;
    }
}
