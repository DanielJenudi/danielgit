/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 22/09/22
- Reviwer: Yaron
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __RD12123_DISPATCHER_HPP__
#define __RD12123_DISPATCHER_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <list> // list

namespace ilrd
{
    template <class EVENT>
    class Dispatcher;

    template <class EVENT>
    class Listener
    {
    public:
        Listener();
        virtual ~Listener() noexcept; // dispatcher->RemoveListener(*this)

        Listener(const Listener &other) = delete;
        Listener(Listener &&other) = delete;
        Listener &operator=(const Listener &other) = delete;
        Listener &operator=(Listener &&other) = delete;

    private:
        friend class Dispatcher<EVENT>;

        std::list<Dispatcher<EVENT> *> m_dispatchers;
        virtual void Invoke(const EVENT &) = 0;
        virtual void PublisherDied(void) noexcept = 0;
    };

    template <class EVENT>
    class Default_Listener : public Listener<EVENT>
    {
    private:
        using pub_died_func = void (*)(void);
        using invoke_func = void (*)(const EVENT &);

    public:
        Default_Listener(pub_died_func user_pub_died_func, invoke_func user_invoke_func);

    private:
        pub_died_func m_pub_died_func;
        invoke_func m_invoke_func;
        virtual void Invoke(const EVENT &);
        virtual void PublisherDied(void) noexcept;
    };

    template <class EVENT>
    class Dispatcher
    {
    public:
        Dispatcher();
        Dispatcher(const Dispatcher &other);
        Dispatcher(Dispatcher &&other) = delete;
        Dispatcher &operator=(const Dispatcher &other);
        Dispatcher &operator=(Dispatcher &&other) = delete;
        ~Dispatcher() noexcept;
        void AddListener(Listener<EVENT> *new_listener);
        void RemoveListener(Listener<EVENT> *listener_to_remove) noexcept;
        void Invoke(const EVENT &);

    private:
        std::list<Listener<EVENT> *> m_listeners;
    };

    /***** Listener *****/
    template <class EVENT>
    Listener<EVENT>::Listener()
    {
        // Empty
    }

    template <class EVENT>
    Listener<EVENT>::~Listener() noexcept
    {
        while (!m_dispatchers.empty())
        {
            Dispatcher<EVENT> *current_dis = m_dispatchers.front();

            current_dis->RemoveListener(this);
        }
    }

    /***** Default_Listener *****/
    template <class EVENT>
    Default_Listener<EVENT>::Default_Listener(pub_died_func user_pub_died_func,
                                              invoke_func user_invoke_func)
    {
        m_pub_died_func = user_pub_died_func;
        m_invoke_func = user_invoke_func;
    }

    template <class EVENT>
    void Default_Listener<EVENT>::Invoke(const EVENT &event)
    {
        (*m_invoke_func)(event);
    }

    template <class EVENT>
    void Default_Listener<EVENT>::PublisherDied(void) noexcept
    {
        (*m_pub_died_func)();
    }

    /***** Dispatcher *****/
    template <class EVENT>
    Dispatcher<EVENT>::Dispatcher()
    {
        // Empty
    }

    template <class EVENT>
    Dispatcher<EVENT>::Dispatcher(const Dispatcher &other)
    {
        for (auto runner = other.m_listeners.begin(); runner != other.m_listeners.end(); ++runner)
        {
            AddListener(*runner);
        }
    }

    template <class EVENT>
    Dispatcher<EVENT> &Dispatcher<EVENT>::operator=(const Dispatcher<EVENT> &other)
    {
        if (&other != this)
        {

            while (!m_listeners.empty())
            {
                Listener<EVENT> *current_listener = m_listeners.front();

                current_listener->PublisherDied();
                RemoveListener(current_listener);
            }

            for (auto runner = other.m_listeners.begin(); runner != other.m_listeners.end(); ++runner)
            {
                AddListener(*runner);
            }
        }

        return *this;
    }

    template <class EVENT>
    Dispatcher<EVENT>::~Dispatcher() noexcept
    {

        while (!m_listeners.empty())
        {
            Listener<EVENT> *current_listener = m_listeners.front();

            current_listener->PublisherDied();
            RemoveListener(current_listener);
        }
    }

    template <class EVENT>
    void Dispatcher<EVENT>::AddListener(Listener<EVENT> *new_listener)
    {
        new_listener->m_dispatchers.push_back(this);
        m_listeners.push_back(new_listener);
    }

    template <class EVENT>
    void Dispatcher<EVENT>::RemoveListener(Listener<EVENT> *listener_to_remove) noexcept
    {
        listener_to_remove->m_dispatchers.remove(this);
        m_listeners.remove(listener_to_remove);
    }

    template <class EVENT>
    void Dispatcher<EVENT>::Invoke(const EVENT &event)
    {
        for (auto runner = m_listeners.begin(); runner != m_listeners.end(); ++runner)
        {
            (*runner)->Invoke(event);
        }
    }

} // namespace ilrd

#endif //__RD12123_DISPATCHER_HPP__