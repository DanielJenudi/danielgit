#include <cstring> /* strcpy */
#include <iostream>

#include "rcstring.hpp"

const size_t g_max_input_len = 100;

namespace ilrd
{

    typedef struct rc_data
    {
        size_t m_binded_strings;
        size_t m_len;
        char m_str[1];
    } rc_data_t;

    static rc_data_t *CreatRC(const char *str);

    RCString::RCString(const char *str)
    {
        m_rc = CreatRC(str);
    }

    RCString::~RCString() throw()
    {

        if (1 == m_rc->m_binded_strings)
        {
            operator delete(m_rc);
            m_rc = 0;
        }
        else
        {
            --m_rc->m_binded_strings;
        }
    }

    RCString::RCString(const RCString &other) throw() : m_rc(other.m_rc)
    {
        ++m_rc->m_binded_strings;
    }

    RCString &RCString::operator=(const RCString &other) throw()
    {
        if (m_rc != other.m_rc)
        {
            this->~RCString();
            m_rc = other.m_rc;
            ++m_rc->m_binded_strings;
        }

        return *this;
    }

    size_t RCString::Length() const throw()
    {
        return m_rc->m_len;
    }

    const char *RCString::RCstr() const throw()
    {
        return m_rc->m_str;
    }

    char &RCString::operator[](size_t pos)
    {
        const char *prev_str = RCstr();

        if (1 != m_rc->m_binded_strings)
        {
            --m_rc->m_binded_strings;
            m_rc = CreatRC(prev_str);
        }

        return m_rc->m_str[pos];
    }

    char RCString::operator[](size_t pos) const
    {
        return m_rc->m_str[pos];
    }

    bool operator==(const RCString &s1, const RCString &s2) throw()
    {
        return (0 == strcmp(s1.RCstr(), s2.RCstr()));
    }
    bool operator!=(const RCString &s1, const RCString &s2) throw()
    {
        return (0 != strcmp(s1.RCstr(), s2.RCstr()));
    }
    bool operator>(const RCString &s1, const RCString &s2) throw()
    {
        return (0 < strcmp(s1.RCstr(), s2.RCstr())) ? true : false;
    }

    bool operator<(const RCString &s1, const RCString &s2) throw()
    {
        return (0 > strcmp(s1.RCstr(), s2.RCstr())) ? true : false;
    }

    std::ostream &operator<<(std::ostream &os, const RCString &x)
    {
        return os << x.RCstr();
    }

    std::istream &operator>>(std::istream &is, RCString &x)
    {
        char new_str[g_max_input_len] = {0};

        is.getline(new_str, (g_max_input_len - 1));

        x = new_str;

        return is;
    }

    static rc_data_t *CreatRC(const char *str)
    {
        rc_data_t *rc = 0;
        size_t len = strlen(str);

        rc = static_cast<rc_data *>(operator new(sizeof(rc_data) + len));

        rc->m_len = len;
        rc->m_binded_strings = 1;
        memcpy(rc->m_str, str, len + 1);

        return rc;
    }
}