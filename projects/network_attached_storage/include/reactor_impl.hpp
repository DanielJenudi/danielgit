#ifndef __RD_12123_REACTOR_IMPL_HPP__
#define __RD_12123_REACTOR_IMPL_HPP__

#include <functional>  /* function */
#include <sys/types.h> /* fd_set */

#include "logger.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    class Reactor_Impl
    {
    public:
        enum Operation
        {
            READ,
            WRITE,
            EXCEPTION
        };

        explicit Reactor_Impl();
        Reactor_Impl(const Reactor_Impl &) = delete;
        Reactor_Impl(Reactor_Impl &&) = delete;
        const Reactor_Impl &operator=(const Reactor_Impl &) = delete;
        const Reactor_Impl &operator=(Reactor_Impl &&) = delete;
        void Reactor_Impl_Add(int fd, std::function<void()> func, Operation op);
        void Reactor_Impl_Remove(int fd, Operation op) noexcept;
        std::pair<int, Operation> Reactor_Impl_Run(); // blocking function

        const std::pair<int, Operation> BAD_PAIR;

    private:
        int m_max_fd;

        fd_set m_read_set;
        fd_set m_write_set;
        fd_set m_excep_set;

        Logger *m_log;
        void FindMaxFd();
    };

}; // namespace ilrd

#endif //__RD_12123_REACTOR_IMPL_HPP__