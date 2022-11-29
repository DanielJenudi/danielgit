#include <cstring>/* strlen, strcpy */

#include "tricky_string.hpp"

namespace ilrd
{

    size_t String::counter = 0;

    String::String(const char *str_) : m_str(new char[strlen(str_) + 1])
    {
        strcpy(m_str, str_);
        ++counter;
    }

    String::String(const String &other_) : m_str(new char[other_.Length() + 1])
    {
        strcpy(m_str, other_.Cstr());
        ++counter;
    }

    String::~String()
    {
        delete[] m_str;
        m_str = NULL;

        --counter;
    }

    void String::operator=(const String &other_)
    {
        if (0 != strcmp(other_.Cstr(), m_str))
        {
            delete[] m_str;
            m_str = NULL;

            m_str = new char[other_.Length() + 1];
            strcpy(m_str, other_.Cstr());
        }
    }

    void String::operator=(const char &other_)
    {
        memset(m_str, other_, this->Length());
    }

    size_t String::Length() const
    {
        return strlen(m_str);
    }

    const char *String::Cstr() const
    {
        return m_str;
    }

    size_t String::GetInstances()
    {
        return counter;
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
