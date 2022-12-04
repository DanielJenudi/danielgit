/* -------------------------------------------------------------------------- *
 * FILENAME      -    dir_monitor.hpp
 * ---------------------------------------------------------------------------*
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    20/10/22
 * ---------------------------------------------------------------------------*/

#ifndef __RD_12123_DIR_MONITOR_HPP__
#define __RD_12123_DIR_MONITOR_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

/* -------------------------------------------------------------------------- *
 *                          Includes
 * ---------------------------------------------------------------------------*/
#include <functional>
#include <string>
#include <thread>

namespace ilrd
{
    class DirMonitor
    {

    public:
        explicit DirMonitor(std::string dir_path,
                            std::function<void(std::string)> add_callback);
        ~DirMonitor();

        DirMonitor(const DirMonitor &) = delete;
        DirMonitor(DirMonitor &&) = delete;
        const DirMonitor &operator=(const DirMonitor &) = delete;
        const DirMonitor &operator=(DirMonitor &&) = delete;

        void Run();

    private:
        void RunThread();
        std::function<void(std::string)> m_add_callback;
        std::string m_dir_path;
        std::thread m_run_thread;
        int m_inotify_fd;
        bool m_is_running;
    };
} // namespace ilrd

#endif //__RD_12123_DIR_MONITOR_HPP__