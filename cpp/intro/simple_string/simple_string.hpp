#ifndef __ILRD_RD12123_SIMPLE_STRING_HPP__
#define __ILRD_RD12123_SIMPLE_STRING_HPP__
#include <cstddef> //c size_t
#include <ostream>

namespace ilrd
{
    class String
    {
    public:
        String(const char *str_ = "");           // constructor (includes default)
        String(const String &other_);            // copy constructor
        ~String();                               // destructor
        String &operator=(const String &other_); // assignment operator
        size_t Length() const;                   // get length
        const char *Cstr() const;                // get const char*

    private:
        char *m_str;
    };

    bool operator==(const String &s1, const String &s2);
    bool operator>(const String &s1, const String &s2);
    bool operator<(const String &s1, const String &s2);
    std::ostream &operator<<(std::ostream &os, const String &x);
}

#endif