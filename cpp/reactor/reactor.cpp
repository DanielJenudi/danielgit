#include <sys/types.h> /* fd_set */
#include <iostream>    /* cout */
#include <functional>  /* bind */
#include <string>      /* string */

#include "reactor.hpp"

static const int STDIN_FD = 0;

namespace ilrd
{
    static void CheckSTDIN(Reactor *reactor);

    Reactor::Reactor() : m_is_running(false)
    {
        auto check_stdin_func = std::bind(&CheckSTDIN, this);
        Add(STDIN_FD, check_stdin_func, reactor_operator_t::READ);
    }

    void Reactor::Add(int fd, std::function<void()> func, reactor_operator_t op)
    {
        reactor_impl.Reactor_Impl_Add(fd, func, op);
        m_invoke_map[std::pair<int, reactor_operator_t>(fd, op)] = func;
    }

    void Reactor::Remove(int fd, reactor_operator_t op) noexcept
    {
        m_invoke_map.erase(std::pair<int, reactor_operator_t>(fd, op));
        reactor_impl.Reactor_Impl_Remove(fd, op);
    }

    void Reactor::Run()
    {
        std::cout << "Reactor is running,\nType stop for exit.\n";

        m_is_running = true;

        while (m_is_running)
        {
            std::pair<int, reactor_operator_t> map_key = reactor_impl.Reactor_Impl_Run();
            (m_invoke_map[map_key])();
        }
    }

    static void CheckSTDIN(Reactor *reactor)
    {
        std::string msg_recived;
        std::cin >> msg_recived;

        if ("stop" == msg_recived)
        {
            reactor->Stop();
        }
    }

    void Reactor::Stop()
    {
        m_is_running = false;
    }
}
