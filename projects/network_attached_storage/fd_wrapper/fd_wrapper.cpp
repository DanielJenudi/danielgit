#include <unistd.h>

#include "fd_wrapper.hpp"

namespace ilrd
{

    FileDesc::FileDesc(int fd) : m_fd(fd), m_cref(new size_t(1))
    {
        // empty
    }

    FileDesc::FileDesc(const FileDesc &other) : m_fd(other.m_fd), m_cref(other.m_cref)
    {
        ++(*m_cref);
    }

    const FileDesc &FileDesc::operator=(const FileDesc &other)
    {
        if (this != &other)
        {
            if (*(m_cref) == 1)
            {
                delete m_cref;
                m_cref = 0;
            }
            else
            {
                --(*m_cref);
            }

            m_cref = other.m_cref;
            m_fd = other.m_fd;

            ++(*m_cref);
        }

        return *this;
    }

    int FileDesc::GetFD() const
    {
        return m_fd;
    }

    FileDesc::~FileDesc()
    {
        if (*(m_cref) == 1)
        {
            close(m_fd);
            delete m_cref;
            m_cref = 0;
        }
        else
        {
            --(*m_cref);
        }
    }
}