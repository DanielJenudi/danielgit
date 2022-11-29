/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 6/9/22
- Reviewer: Yaniv Meshullam
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __RD12123_BIT_ARRAY_SOURCES_HPP__
#define __RD12123_BIT_ARRAY_SOURCES_HPP__

#include <string>
#include <vector>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

static const unsigned char g_reset_end[8] = {
    0xff, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f};

/* ~~~~~ Functors ~~~~~ */

/* --- Flip_All_Class --- */
class Flip_All_Class
{
public:
    void operator()(unsigned char &byte);
};

/* --- Count_Class --- */
class Count_Class
{
public:
    size_t operator()(size_t count, unsigned char byte);
};

/* --- To_String_Class --- */
class To_String_Class
{
public:
    std::string operator()(std::string str, unsigned char byte);
};

/* --- OperatorOR_Class --- */
class OperatorOR_Class
{
public:
    OperatorOR_Class(const std::vector<unsigned char> *vector, size_t byte_index = 0);
    void operator()(unsigned char &byte);

private:
    const std::vector<unsigned char> *m_vector;
    size_t m_byte_index;
};

/* --- OperatorAND_Class --- */
class OperatorAND_Class
{
public:
    OperatorAND_Class(const std::vector<unsigned char> *vector, size_t byte_index = 0);
    void operator()(unsigned char &byte);

private:
    const std::vector<unsigned char> *m_vector;
    size_t m_byte_index;
};

/* --- OperatorXOR_Class --- */
class OperatorXOR_Class
{
public:
    OperatorXOR_Class(const std::vector<unsigned char> *vector, size_t byte_index = 0);
    void operator()(unsigned char &byte);

private:
    const std::vector<unsigned char> *m_vector;
    size_t m_byte_index;
};

/* ~~~~~ Help Funcs ~~~~~ */

void SetBitOn(size_t pos, unsigned char &byte);
void SetBitOff(size_t pos, unsigned char &byte);

template <size_t N>
void ResetUnUsedEnd(unsigned char &byte)
{
    byte &= g_reset_end[(N % 8)];
}

#endif //__RD12123_BIT_ARRAY_SOURCES_HPP__
