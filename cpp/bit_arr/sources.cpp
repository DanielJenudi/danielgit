/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 6/9/22
- Reviewer: Yaniv Meshullam
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "sources.hpp"

/* ~~~~~ Flip_All_Class ~~~~~ */

void Flip_All_Class::operator()(unsigned char &byte)
{
    byte = ~byte;
}

/* ~~~~~ Count_Class ~~~~~ */

size_t Count_Class::operator()(size_t count, unsigned char byte)
{
    static const int lut_nibble_s[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3,
        4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4,
        4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2,
        3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
        4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4,
        5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
        3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2,
        3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
        4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
        6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5,
        5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6,
        7, 7, 8};

    return count + lut_nibble_s[byte];
}

/* ~~~~~ To_String_Class ~~~~~ */

std::string To_String_Class::operator()(std::string str, unsigned char byte)
{
    static const unsigned char ascii_dif = 48;

    str.insert(str.end(), ((byte >> 0) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 1) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 2) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 3) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 4) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 5) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 6) & 1) + ascii_dif);
    str.insert(str.end(), ((byte >> 7) & 1) + ascii_dif);

    return str;
}

/* ~~~~~ OperatorOR_Class ~~~~~ */

OperatorOR_Class::OperatorOR_Class(const std::vector<unsigned char> *vector,
                                   size_t byte_index)
    : m_vector(vector), m_byte_index(byte_index)
{
    // empty
}

void OperatorOR_Class::operator()(unsigned char &byte)
{
    byte |= m_vector->at(m_byte_index);
    ++m_byte_index;
}

/* ~~~~~ OperatorAND_Class ~~~~~ */

OperatorAND_Class::OperatorAND_Class(const std::vector<unsigned char> *vector,
                                     size_t byte_index)
    : m_vector(vector), m_byte_index(byte_index)
{
    // empty
}

void OperatorAND_Class::operator()(unsigned char &byte)
{
    byte &= m_vector->at(m_byte_index);
    ++m_byte_index;
}

/* ~~~~~ OperatorXOR_Class ~~~~~ */

OperatorXOR_Class::OperatorXOR_Class(const std::vector<unsigned char> *vector,
                                     size_t byte_index)
    : m_vector(vector), m_byte_index(byte_index)
{
    // empty
}

void OperatorXOR_Class::operator()(unsigned char &byte)
{
    byte ^= m_vector->at(m_byte_index);
    ++m_byte_index;
}

/* ~~~~~ Help Funcs ~~~~~ */

void SetBitOn(size_t pos, unsigned char &byte)
{
    unsigned char mask = 1 << pos;
    byte |= mask;
}

void SetBitOff(size_t pos, unsigned char &byte)
{
    unsigned char mask = 1 << pos;
    byte &= (~mask);
}
