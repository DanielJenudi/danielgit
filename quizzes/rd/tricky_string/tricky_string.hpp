#ifndef __ILRD_RD12123_SIMPLE_STRING_HPP__
#define __ILRD_RD12123_SIMPLE_STRING_HPP__
#include <cstddef> //c size_t
#include <ostream>

namespace ilrd
{
    class String
    {
    public:
        String(const char *str_ = "ABC");     // constructor (includes default)
        String(const String &other_);         // copy constructor
        ~String();                            // destructor
        void operator=(const String &other_); // assignment operator
        void operator=(const char &other_);   // assignment operator
        size_t Length() const;                // get length
        const char *Cstr() const;             // get const char*
        static size_t GetInstances();

    private:
        char *m_str;
        static size_t counter;
    };

    bool operator==(const String &s1, const String &s2);
    bool operator>(const String &s1, const String &s2);
    bool operator<(const String &s1, const String &s2);
    std::ostream &operator<<(std::ostream &os, const String &x);
}

#endif