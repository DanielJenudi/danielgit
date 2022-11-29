/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 13/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __RD12123_LOGGER_HPP__
#define __RD12123_LOGGER_HPP__

#include "handleton.hpp"
#include "thread_pool.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    class Logger
    {
    public:
        void Log(const std::string &log);
        void SetPath(const std::string &path);

    private:
        Logger(const std::string &path = "./logger.txt");
        friend class Handleton<Logger>;
        ThreadPool m_thread_pool;
        std::string m_path;
    };
}

#endif //__RD12123_LOGGER_HPP__