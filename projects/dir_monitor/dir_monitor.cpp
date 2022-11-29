#include <sys/inotify.h> // inotify
#include <unistd.h>      // read, write
#include <thread>        // threads
#include <fstream>
#include <cstdio>

#include "dir_monitor.hpp"

const size_t SIZE_OF_EVENT = sizeof(struct inotify_event);
const size_t EVENT_BUFFER_SIZE = 4096;

namespace ilrd
{

    DirMonitor::DirMonitor(std::string dir_path,
                           std::function<void(std::string dir_path)> add_callback)
        : m_add_callback(add_callback), m_dir_path(dir_path),
          m_inotify_fd(inotify_init()), m_is_running(false)
    {
        // empty
    }
    DirMonitor ::~DirMonitor()
    {
        if (true == m_is_running)
        {

            m_is_running = false;

            std::string path(m_dir_path);
            path.append("/stop_file.txt");

            std::ifstream myfile;
            myfile.open(path.c_str());

            std::ofstream{path};
            remove(path.c_str());

            m_run_thread.join();
        }
    }

    void DirMonitor::Run()
    {
        m_run_thread = std::thread(&DirMonitor::RunThread, this);
    }

    void DirMonitor::RunThread()
    {
        m_is_running = true;

        inotify_add_watch(m_inotify_fd, m_dir_path.c_str(), IN_CREATE | IN_MOVED_TO);
        char event_buffer[EVENT_BUFFER_SIZE] = {0};

        while (m_is_running)
        {
            long len = read(m_inotify_fd, event_buffer, EVENT_BUFFER_SIZE);

            if (false == m_is_running)
            {
                break;
            }

            if (-1 == len)
            {
                perror("read FAIL\n");
                continue;
            }

            struct inotify_event *event = nullptr;
            for (char *ptr = event_buffer;
                 ptr < event_buffer + len;
                 ptr += sizeof(struct inotify_event) + event->len)
            {
                event = (struct inotify_event *)(ptr);
                std::string final_path = m_dir_path;
                final_path.append("/").append(event->name);
                m_add_callback(final_path);
            }
        }
    }
}
