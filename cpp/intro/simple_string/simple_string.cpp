#include <cstring>/* strlen, strcpy */

#include "simple_string.hpp"

namespace ilrd
{
    String::String(const char *str_) : m_str(new char[strlen(str_) + 1])
    {
        strcpy(m_str, str_);
    }

    String::String(const String &other_) : m_str(new char[other_.Length() + 1])
    {
        strcpy(m_str, other_.Cstr());
    }

    String::~String()
    {
        delete[] m_str;
        m_str = NULL;
    }

    String &String::operator=(const String &other_)
    {
        if (0 != strcmp(other_.Cstr(), m_str))
        {
            delete[] m_str;
            m_str = NULL;

            m_str = new char[other_.Length() + 1];
            strcpy(m_str, other_.Cstr());
        }

        return *this;
    }

    size_t String::Length() const
    {
        return strlen(m_str);
    }

    const char *String::Cstr() const
    {
        return m_str;
    }

    bool operator==(const String &s1, const String &s2)
    {
        return !strcmp(s1.Cstr(), s2.Cstr());
    }

    bool operator>(const String &s1, const String &s2)
    {
        return (0 < strcmp(s1.Cstr(), s2.Cstr()));
    }

    bool operator<(const String &s1, const String &s2)
    {
        return (0 > strcmp(s1.Cstr(), s2.Cstr()));
    }

    std::ostream &operator<<(std::ostream &os, const String &x)
    {
        return os << x.Cstr();
    }
}
