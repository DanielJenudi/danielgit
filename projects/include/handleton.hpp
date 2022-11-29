/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer:
 *Date: 15.09.22
 ******************************************************************************/

#ifndef __RD12123_HANDLETON_HPP__
#define __RD12123_HANDLETON_HPP__

#include <boost/thread/mutex.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/atomic/atomic.hpp>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

static boost::mutex g_lock;

namespace ilrd
{
    template <class Base>
    class Handleton : private boost::noncopyable
    {
    public:
        static Base *GetInstance();

    private:
        Handleton();
        static void DestroyHandleton();
        static boost::atomic<Base *> m_usr_singleton;
    };

#ifdef SHARED_LIBRARY
    template <class Base>
    boost::atomic<Base *> Handleton<Base>::m_usr_singleton(nullptr);

    template <class Base>
    Base *Handleton<Base>::GetInstance()
    {

        if (nullptr == m_usr_singleton)
        {
            boost::unique_lock<boost::mutex> ul(g_lock);

            if (nullptr == m_usr_singleton)
            {
                Base *temp = new Base;
                m_usr_singleton.store(temp, boost::memory_order_release);

                std::atexit(DestroyHandleton);
            }
        }

        return m_usr_singleton;
    }

    template <class Base>
    void Handleton<Base>::DestroyHandleton()
    {
        boost::unique_lock<boost::mutex> ul(g_lock);

        delete m_usr_singleton;
        m_usr_singleton = nullptr;
    }
#endif // SHARED_LIBRARY
}

#endif //__RD12123_HANDLETON_HPP__