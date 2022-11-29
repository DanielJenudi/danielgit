#include <sys/types.h> /* fd_set */
#include <iostream>    /* cout */
#include <functional>  /* bind */
#include <string>      /* string */

#include "reactor_impl.hpp"

#define MAX(Y, X) ((Y) > (X) ? (Y) : (X))

using namespace ilrd;

static const int SELECT_FAIL = -1;
static const int STDIN_FD = 0;
static const size_t MAXBUFFER = 1024;

namespace ilrd
{

    Reactor_Impl::Reactor_Impl() : BAD_PAIR(-1, READ), m_max_fd(0),
                                   m_log(Singleton<Logger>::GetInstance())
    {
        FD_SET(STDIN_FD, &m_read_set);
    }

    void Reactor_Impl::Reactor_Impl_Add(int fd, std::function<void()> func, Operation op)
    {
        (void)func;

        switch (op)
        {
        case (READ):
            FD_SET(fd, &m_read_set);
            break;

        case (WRITE):
            FD_SET(fd, &m_write_set);
            break;

        case (EXCEPTION):
            FD_SET(fd, &m_excep_set);
            break;
        }

        m_max_fd = MAX(m_max_fd, fd);

        m_log->Log(std::string("Add FD: " + std::to_string(fd) +
                               " Current Max FD: " + std::to_string(m_max_fd)));
    }

    void Reactor_Impl::Reactor_Impl_Remove(int fd, Operation op) noexcept
    {
        switch (op)
        {
        case (READ):
            FD_CLR(fd, &m_read_set);
            break;

        case (WRITE):
            FD_CLR(fd, &m_write_set);
            break;

        case (EXCEPTION):
            FD_CLR(fd, &m_excep_set);
            break;
        }

        FindMaxFd();
        m_log->Log(std::string("Remove FD: " + std::to_string(fd) +
                               " Current Max FD: " + std::to_string(m_max_fd)));
    }

    void Reactor_Impl::FindMaxFd()
    {
        for (int i = m_max_fd; i >= 0; --i)
        {
            if (FD_ISSET(i, &m_read_set))
            {
                m_max_fd = i;
                break;
            }

            if (FD_ISSET(i, &m_write_set))
            {
                m_max_fd = i;
                break;
            }

            if (FD_ISSET(i, &m_excep_set))
            {
                m_max_fd = i;
                break;
            }
        }
    }

    std::pair<int, Reactor_Impl::Operation> Reactor_Impl::Reactor_Impl_Run()
    {
        fd_set read_set = m_read_set;
        fd_set write_set = m_write_set;
        fd_set excep_set = m_excep_set;

        if (SELECT_FAIL == select(m_max_fd + 1,
                                  &read_set, &write_set, &excep_set, nullptr))
        {
            m_log->Log(std::string("Select Fail"));
            perror("Select fail");
            return BAD_PAIR;
        }

        for (int i = 0; i <= m_max_fd; ++i)
        {
            if (FD_ISSET(i, &read_set))
            {
                m_log->Log(std::string("Invoke in READ mode FD: " + std::to_string(i)));
                return std::pair<int, Operation>(i, READ);
            }

            if (FD_ISSET(i, &write_set))
            {
                m_log->Log(std::string("Invoke in WRITE mode FD: " + std::to_string(i)));
                return std::pair<int, Operation>(i, WRITE);
            }

            if (FD_ISSET(i, &excep_set))
            {
                m_log->Log(std::string("Invoke in EXCEPTION mode FD: " + std::to_string(i)));
                return std::pair<int, Operation>(i, EXCEPTION);
            }
        }

        return BAD_PAIR;
    }
}
