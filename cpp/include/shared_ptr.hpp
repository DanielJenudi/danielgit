/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Hagar
 *Date: 01.09.22
 ******************************************************************************/

#ifndef __ILRD_RD12123_SHARED_PTR_HPP__
#define __ILRD_RD12123_SHARED_PTR_HPP__

#include <cstddef>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    template <class T>
    class Shared_Pointer
    {
    public:
        /*undefined behaviour if pointee does not point to dynamically allocated object*/
        explicit Shared_Pointer(T *pointee = 0);
        Shared_Pointer(const Shared_Pointer<T> &other) noexcept; // non-explicit
        template <class Y>
        Shared_Pointer(const Shared_Pointer<Y> &other) noexcept; // non-explicit
        Shared_Pointer<T> &operator=(const Shared_Pointer<T> &other) noexcept;
        template <class Y>
        Shared_Pointer<T> &operator=(const Shared_Pointer<Y> &other) noexcept;
        ~Shared_Pointer() noexcept;
        T &operator*() const;
        T *operator->() const noexcept;
        T *GetPtr() const noexcept;

    private:
        template <class Y>
        friend size_t *GetRC(const Shared_Pointer<Y> &);
        T *m_ptr;
        size_t *m_reference_count;
    };

    template <class T>
    Shared_Pointer<T>::Shared_Pointer(T *pointee)
        : m_ptr(pointee),
          m_reference_count(new size_t(1))
    {
        // empty
    }

    template <class T>
    Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer<T> &other) noexcept
        : m_ptr(other.GetPtr()),
          m_reference_count(GetRC(other))
    {
        ++*m_reference_count;
    }

    template <class T>
    template <class Y>
    Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer<Y> &other) noexcept
        : m_ptr(other.GetPtr()),
          m_reference_count(GetRC(other))
    {
        ++*m_reference_count;
    }

    template <class T>
    Shared_Pointer<T> &Shared_Pointer<T>::operator=(const Shared_Pointer<T> &other) noexcept
    {
        if (this->GetPtr() != other.GetPtr())
        {
            this->~Shared_Pointer();

            m_ptr = other.GetPtr();

            m_reference_count = GetRC(other);
            ++*m_reference_count;
        }

        return *this;
    }

    template <class T>
    template <class Y>
    Shared_Pointer<T> &Shared_Pointer<T>::operator=(const Shared_Pointer<Y> &other) noexcept
    {
        if (this->GetPtr() != other.GetPtr())
        {
            this->~Shared_Pointer();

            m_ptr = other.GetPtr();

            m_reference_count = GetRC(other);
            ++*m_reference_count;
        }

        return *this;
    }

    template <class T>
    Shared_Pointer<T>::~Shared_Pointer() noexcept
    {
        if (1 == *m_reference_count)
        {
            delete m_reference_count;
            delete m_ptr;
        }
        else
        {
            --*m_reference_count;
        }
    }

    template <class T>
    T &Shared_Pointer<T>::operator*() const
    {
        return *m_ptr;
    }

    template <class T>
    T *Shared_Pointer<T>::operator->() const noexcept
    {
        return m_ptr;
    }

    template <class T>
    T *Shared_Pointer<T>::GetPtr() const noexcept
    {
        return m_ptr;
    }

    template <class Y>
    size_t *GetRC(const Shared_Pointer<Y> &sp)
    {
        return sp.m_reference_count;
    }

    template <class T, class Y>
    bool operator==(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs)
    {
        return lhs.GetPtr() == rhs.GetPtr();
    }

    template <class T, class Y>
    bool operator!=(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs)
    {
        return lhs.GetPtr() != rhs.GetPtr();
    }
}
#endif //__ILRD_RD12123_SHARED_PTR_HPP__