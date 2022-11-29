#ifndef __ILRD_RD12123_RCSTRING_HPP__
#define __ILRD_RD12123_RCSTRING_HPP__

#include <iosfwd>  /*std*/
#include <cstddef> /*c size_t*/

namespace ilrd
{
    class RCString
    {
    public:
        RCString(const char *str = "");
        RCString(const RCString &other) throw();
        RCString &operator=(const RCString &other) throw();
        ~RCString() throw();
        size_t Length() const throw();
        const char *RCstr() const throw();
        char &operator[](size_t pos);
        char operator[](size_t pos) const;

    private:
        typedef struct rc_data rc_data_t;
        rc_data_t *m_rc;
    };
    bool operator==(const RCString &s1, const RCString &s2) throw();
    bool operator!=(const RCString &s1, const RCString &s2) throw();
    bool operator>(const RCString &s1, const RCString &s2) throw();
    bool operator<(const RCString &s1, const RCString &s2) throw();
    std::ostream &operator<<(std::ostream &os, const RCString &x);
    std::istream &operator>>(std::istream &is, RCString &x);
}

#endif
