/* -------------------------------------------------------------------------- *
 * FILENAME      -    nbd_comm.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    02/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_FD_HPP__
#define __RD12123_FD_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif
#include <string>
#include <climits>

namespace ilrd
{

    class FileDesc
    {

    public:
        explicit FileDesc(int fd = INT_MAX);
        FileDesc(const FileDesc &other);
        const FileDesc &operator=(const FileDesc &other);
        int GetFD() const;
        ~FileDesc();

    private:
        int m_fd;
        size_t *m_cref;
    };

}

#endif //__RD12123_FD_HPP__