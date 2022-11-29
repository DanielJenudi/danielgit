/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 13/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <unistd.h> // nice

#include "thread_pool.hpp"

using namespace ilrd;

static bool g_is_threads_running = false;
static std::condition_variable g_cond_var_pause_lock;

/***** ThreadPool *****/

ThreadPool::ThreadPool(size_t n_threads, size_t niceness)
    : m_kill_thread_task(new Default_Task([]() {}))
{
    errno = 0;

    if ((-1 == nice(niceness)) && (0 != errno))
    {
        throw std::system_error(errno, std::generic_category());
    }

    for (size_t i = 0; i < n_threads; ++i)
    {
        m_thread_queue.push_back(std::unique_ptr<ThreadUnit>(new ThreadUnit(this)));
    }
}

ThreadPool::~ThreadPool()
{
    if (0 != m_thread_queue.size())
    {
        g_is_threads_running = true;
        while (!m_task_queue.IsEmpty())
        {
            this->Run();
        }

        SetNumberOfThreads(0);
    }
    else
    {
        this->Stop();
    }
}

void ThreadPool::Add(std::shared_ptr<Task> function, PRIORITY pr)
{
    Manager_Add(function, static_cast<MANAGER_PRIORITY>(pr));
}

void ThreadPool::Manager_Add(std::shared_ptr<Task> function, MANAGER_PRIORITY pr)
{
    m_task_queue.Push(std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY>(function, pr));
}

void ThreadPool::Run() noexcept
{
    std::unique_lock<std::mutex> ul(modify_threads_q_lock);

    g_is_threads_running = true;

    g_cond_var_pause_lock.notify_all();
}

void ThreadPool::Pause() noexcept
{
    std::unique_lock<std::mutex> ul(modify_threads_q_lock);

    g_is_threads_running = false;
}

void ThreadPool::Stop() noexcept
{
    std::unique_lock<std::mutex> ul(modify_threads_q_lock);

    std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> retval;

    g_is_threads_running = false;

    while (!m_task_queue.IsEmpty())
    {
        m_task_queue.Pop(retval, std::chrono::milliseconds(100));
    }
}

void ThreadPool::SetNumberOfThreads(size_t n_threads)
{

    std::unique_lock<std::mutex> ul(modify_threads_q_lock);

    if (m_thread_queue.size() > n_threads)
    {
        bool pool_status = g_is_threads_running;
        g_is_threads_running = false;

        size_t diff = m_thread_queue.size() - n_threads;

        for (size_t i = 0; i < diff; ++i)
        {
            Manager_Add(m_kill_thread_task, MANAGER_RELEASE_POP);
        }

        for (auto thread_list_runner = m_thread_queue.begin();
             (0 != diff);
             thread_list_runner = (thread_list_runner != m_thread_queue.end()) ? thread_list_runner : m_thread_queue.begin())
        {
            if (PAUSE == thread_list_runner->get()->GetStatus())
            {
                thread_list_runner->get()->SetStatus(KILL);
                g_cond_var_pause_lock.notify_all();
                thread_list_runner = m_thread_queue.erase(thread_list_runner);

                --diff;
            }
            else
            {
                ++thread_list_runner;
            }
        }

        g_is_threads_running = pool_status;
    }
    else
    {
        size_t diff = n_threads - m_thread_queue.size();

        for (size_t i = 0; i < diff; ++i)
        {
            m_thread_queue.push_back(std::unique_ptr<ThreadUnit>(new ThreadUnit(this)));
        }
    }
}

/***** ThreadUnit *****/

ThreadPool::ThreadUnit::ThreadUnit(ThreadPool *m_thread_pool)
    : m_thread_pool(m_thread_pool), m_thred_status(PAUSE), m_is_exit(false),
      m_thread(std::thread(&ThreadPool::ThreadUnit::ThreadFunc, this))
{
    // empty
}

ThreadPool::ThreadUnit::~ThreadUnit()
{
    while (!m_is_exit)
    {
        m_thred_status = KILL;
        g_cond_var_pause_lock.notify_all();
    }

    m_thread.join();
}

void ThreadPool::ThreadUnit::ThreadFunc()
{
    std::mutex pauselock;
    std::unique_lock<std::mutex> ul(pauselock);

    std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> cur_task;

    do
    {
        if (false == g_is_threads_running)
        {
            g_cond_var_pause_lock.wait(ul);
        }

        while ((false != g_is_threads_running) && (KILL != m_thred_status))
        {
            m_thred_status = RUN;

            m_thread_pool->m_task_queue.Pop(cur_task);
            if ((false == g_is_threads_running) && (MANAGER_RELEASE_POP != cur_task.second))
            {
                m_thread_pool->Manager_Add(cur_task.first, cur_task.second);
            }
            else
            {
                (*cur_task.first)();
            }

            m_thred_status = PAUSE;
        }

    } while ((KILL != m_thred_status));

    m_is_exit = true;
}

THREAD_STATUS ThreadPool::ThreadUnit::GetStatus()
{
    return m_thred_status;
}

void ThreadPool::ThreadUnit::SetStatus(THREAD_STATUS status)
{
    m_thred_status = status;
}

/***** Task *****/

Task::~Task()
{
    // empty
}

/***** Default_Task *****/

Default_Task::Default_Task(std::function<void()> func) : m_func(func)
{
    // empty
}

Default_Task::~Default_Task()
{
    // empty
}

void Default_Task::operator()()
{
    m_func();
}

/***** Compare_Functor *****/

bool ThreadPool::Compare_Functor::operator()(
    const std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> &lhs,
    const std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> &rhs) const
{
    return (lhs.second > rhs.second);
}
