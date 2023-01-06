#ifndef __RC_STR__
#define __RC_STR__

#include <iosfwd>

namespace ilrd
{

    class RC_STR
    {
    public:
        RC_STR(const char *str = "");
        RC_STR(const RC_STR &other);
        RC_STR &operator=(const RC_STR &other);

        const char *GetStr() const throw();

        ~RC_STR();

    private:
        typedef struct rc_data rc_data_t;
        rc_data_t *m_rc;
    };

    std::ostream &operator<<(std::ostream &stream, const RC_STR &rc_str);

}
#endif /* __RC_STR__ */