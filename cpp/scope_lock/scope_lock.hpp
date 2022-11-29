/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Yhaly
 *Date: 22.08.22
 ******************************************************************************/

#ifndef __SCOPELOCK_HPP__
#define __SCOPELOCK_HPP__

#include <iostream> // cout

#include <boost/core/noncopyable.hpp>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    // T must implement Lock() and Unlock() functions
    template <typename T>
    class ScopeLock : private boost::noncopyable
    {
    public:
        explicit ScopeLock(T &lock);
        ~ScopeLock() noexcept;

    private:
        T &m_lock;
    };

    template <typename T>
    ScopeLock<T>::ScopeLock(T &lock) : m_lock(lock)
    {
        m_lock.lock();
    }

    template <typename T>
    ScopeLock<T>::~ScopeLock() noexcept
    {
        try
        {
            m_lock.unlock();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

#endif //__SCOPELOCK_HPP__