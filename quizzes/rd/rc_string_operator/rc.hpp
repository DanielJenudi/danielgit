#include <cstddef> // size_t

namespace ilrd
{

    class String
    {
    public:
        explicit String(const char *str_ = "");
        ~String();
        String &operator=(const String &other);
        String &operator=(const char *str_);
        char *GetStr() const;

    private:
        struct RC
        {
            char *m_str;
            size_t m_count;
        };

        RC *m_rc;
    };
}