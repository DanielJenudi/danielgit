/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 6/9/22
- Reviewer: Yaniv Meshullam
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __RD12123_BIT_ARRAY_HPP__
#define __RD12123_BIT_ARRAY_HPP__

#include <cstddef>   // size_t
#include <string>    // string
#include <vector>    // vector
#include <algorithm> // for_each
#include <numeric>   // accumulate
#include <stdexcept> // out_of_range

#include "sources.hpp" // functors

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

static const size_t g_bits_in_byte = 8;

namespace ilrd
{

    template <size_t N>
    class BitArray
    {
    private:
        class BitHandler;

    public:
        explicit BitArray();
        BitHandler operator[](size_t pos);
        bool operator[](size_t pos) const;
        bool operator==(const BitArray &other) const noexcept;
        bool operator!=(const BitArray &other) const noexcept;
        bool Get(size_t pos) const;
        BitArray &Set(size_t pos, bool value);
        BitArray &SetAll(bool value) noexcept;
        BitArray &Flip(size_t pos);
        BitArray &FlipAll() noexcept;
        size_t Count() const noexcept;
        std::string ToString() const;
        BitArray &operator|=(const BitArray &other) noexcept;
        BitArray &operator&=(const BitArray &other) noexcept;
        BitArray &operator^=(const BitArray &other) noexcept;

    private:
        std::vector<unsigned char> m_arr;
        class BitHandler
        {
        public:
            explicit BitHandler(BitArray *arr, size_t pos) noexcept;
            BitHandler &operator=(bool other) noexcept;
            operator bool() const noexcept;

        private:
            BitHandler &operator=(BitHandler &other) noexcept;

            BitArray *m_arr;
            size_t m_index;
        };
    };

    /* ~~~~~ BitHandler ~~~~~ */

    /* --- Ctor --- */

    template <size_t N>
    BitArray<N>::BitHandler::BitHandler(BitArray<N> *arr, size_t pos) noexcept
        : m_arr(arr), m_index(pos)
    {
        // empty
    }

    /* --- Operators --- */

    template <size_t N>
    typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator=(bool other) noexcept
    {

        m_arr->Set(m_index, other);

        return *this;
    }
    template <size_t N>
    BitArray<N>::BitHandler::operator bool() const noexcept
    {
        unsigned char byte = m_arr->m_arr.at(m_index / 8);
        return ((byte >> (m_index % 8)) & 1);
    }

    /* ~~~~~ BitArray ~~~~~ */

    /* --- Ctor --- */
    template <size_t N>
    BitArray<N>::BitArray()
    {
        size_t num_of_bytes = (N / g_bits_in_byte) + !!(N % g_bits_in_byte);
        m_arr.resize(num_of_bytes);
        ResetUnUsedEnd<N>(m_arr.back());
    }

    /* --- Operators --- */
    template <size_t N>
    typename BitArray<N>::BitHandler BitArray<N>::operator[](size_t pos)
    {
        if (N <= pos)
        {
            throw std::out_of_range("Error: Position out of range");
        }

        return BitArray<N>::BitHandler(this, pos);
    }

    template <size_t N>
    bool BitArray<N>::operator[](size_t pos) const
    {

        size_t byte_location = pos / g_bits_in_byte;
        size_t bit_location = pos - (byte_location * g_bits_in_byte);
        char byte = m_arr[byte_location];

        return !!(byte & (1 << bit_location));
    }

    template <size_t N>
    bool BitArray<N>::operator==(const BitArray &other) const noexcept
    {
        return other.m_arr == m_arr;
    }

    template <size_t N>
    bool BitArray<N>::operator!=(const BitArray &other) const noexcept
    {
        return other.m_arr != m_arr;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator|=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_arr.begin(), m_arr.end(), OperatorOR_Class(&other.m_arr));
        ResetUnUsedEnd<N>(m_arr.back());

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator&=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_arr.begin(), m_arr.end(), OperatorAND_Class(&other.m_arr));
        ResetUnUsedEnd<N>(m_arr.back());

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator^=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_arr.begin(), m_arr.end(), OperatorXOR_Class(&other.m_arr));
        ResetUnUsedEnd<N>(m_arr.back());

        return *this;
    }

    /* --- Member Functions --- */
    template <size_t N>
    bool BitArray<N>::Get(size_t pos) const
    {
        if (N <= pos)
        {
            throw std::out_of_range("Error: Position out of range");
        }

        return (*this)[pos];
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::Set(size_t pos, bool value)
    {
        size_t bit_location = pos / g_bits_in_byte;
        size_t bit_location_in_byte = pos - (bit_location * g_bits_in_byte);
        unsigned char &byte = m_arr.at(bit_location);

        if (value)
        {
            SetBitOn(bit_location_in_byte, byte);
        }
        else
        {
            SetBitOff(bit_location_in_byte, byte);
        }

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::SetAll(bool value) noexcept
    {
        const static int value_lut_s[2] = {0, 0xff};
        std::fill(m_arr.begin(), m_arr.end(), value_lut_s[value]);

        ResetUnUsedEnd<N>(m_arr.back());

        return *this;
    }
    template <size_t N>
    BitArray<N> &BitArray<N>::Flip(size_t pos)
    {
        if (N <= pos)
        {
            throw std::out_of_range("Error: Position out of range");
        }

        bool to_set = !(this->Get(pos));
        this->Set(pos, to_set);
        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::FlipAll() noexcept
    {
        std::for_each(m_arr.begin(), m_arr.end(), Flip_All_Class());

        ResetUnUsedEnd<N>(m_arr.back());

        return *this;
    }

    template <size_t N>
    size_t BitArray<N>::Count() const noexcept
    {
        return std::accumulate(m_arr.begin(), m_arr.end(), 0, Count_Class());
    }

    template <size_t N>
    std::string BitArray<N>::ToString() const
    {
        std::string str;

        str = std::accumulate(m_arr.begin(), m_arr.end(), str, To_String_Class());

        str.resize(N);

        std::reverse(str.begin(), str.end());

        return str;
    }

} // namespace ilrd
#endif //__RD12123_BIT_ARRAY_HPP__