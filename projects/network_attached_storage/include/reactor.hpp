#ifndef __RD_12123_REACTOR_HPP__
#define __RD_12123_REACTOR_HPP__

#include <map>
#include <functional>  /* function */
#include <sys/types.h> /* fd_set */

#include "reactor_impl.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    using reactor_operator_t = Reactor_Impl::Operation;
    const reactor_operator_t read_t = Reactor_Impl::Operation::READ;
    const reactor_operator_t write_t = Reactor_Impl::Operation::WRITE;
    const reactor_operator_t exception_t = Reactor_Impl::Operation::EXCEPTION;

    class Reactor
    {
    public:
        // STDIN(fd = 0) is unavilable for user needs

        explicit Reactor();
        Reactor(const Reactor &) = delete;
        Reactor(Reactor &&) = delete;
        const Reactor &operator=(const Reactor &) = delete;
        const Reactor &operator=(Reactor &&) = delete;
        void Add(int fd, std::function<void()> func, reactor_operator_t op);
        void Remove(int fd, reactor_operator_t op) noexcept;
        void Run(); // blocking function
        void Stop();

    private:
        std::map<std::pair<int, reactor_operator_t>, std::function<void()>> m_invoke_map;
        Reactor_Impl reactor_impl;
        bool m_is_running;
    };
} // namespace ilrd

#endif //__RD_12123_REACTOR_HPP__