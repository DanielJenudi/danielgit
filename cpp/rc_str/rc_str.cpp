#include <cstring>  //strlen
#include <cstddef>  // size_t
#include <iostream> // cout

#include "rc_str.hpp"

namespace ilrd
{

    struct rc_data
    {
        size_t count;
        char str[1];
    };

    typedef struct rc_data rc_data_t;

    static rc_data *Creat_rc_data(const char *str);

    RC_STR::RC_STR(const char *str)
        : m_rc(Creat_rc_data(str))
    {
        // empty
    }

    RC_STR::RC_STR(const RC_STR &other)
    {
        m_rc = other.m_rc;
        ++m_rc->count;
    }

    RC_STR &RC_STR::operator=(const RC_STR &other)
    {
        if (this->m_rc == other.m_rc)
        {
            return *this;
        }

        if (1 == this->m_rc->count)
        {
            operator delete(this->m_rc);
            m_rc = nullptr;
        }
        else
        {
            --this->m_rc->count;
        }

        this->m_rc = other.m_rc;
        ++m_rc->count;

        return *this;
    }

    const char *RC_STR::GetStr() const noexcept
    {
        return m_rc->str;
    }

    RC_STR::~RC_STR()
    {
        if (1 == this->m_rc->count)
        {
            operator delete(this->m_rc);
            m_rc = nullptr;
        }
        else
        {
            --this->m_rc->count;
        }
    }

    static rc_data_t *Creat_rc_data(const char *str)
    {
        rc_data_t *new_rc_data =
            static_cast<rc_data_t *>(operator new(sizeof(rc_data_t) + strlen(str)));

        new_rc_data->count = 1;
        memcpy(new_rc_data->str, str, strlen(str) + 1);

        return new_rc_data;
    }

    std::ostream &operator<<(std::ostream &stream, const RC_STR &rc_str)
    {
        return stream << rc_str.GetStr();
    }
}