/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 13/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __RD12123_THREAD_POOL_HPP__
#define __RD12123_THREAD_POOL_HPP__

#include <functional> // function<>
#include <thread>     // thread
#include <list>       // list
#include <mutex>      // mutex
#include <memory>     // shared ptr

#include "waitable_queue.hpp"
#include "pq_wrapper.hpp"

namespace ilrd
{

    enum PRIORITY
    {
        HIGH = 1,
        MEDIUM,
        LOW
    };

    enum THREAD_STATUS
    {
        RUN = 0,
        PAUSE,
        KILL
    };

    class Task;

    class ThreadPool
    {
    private:
        class ThreadUnit;      // forward declaration
        class Compare_Functor; // forward declaration

        enum MANAGER_PRIORITY
        {
            MANAGER_RELEASE_POP = 0,
            HIGH,
            MEDIUM,
            LOW
        };

    public:
        explicit ThreadPool(size_t n_threads =
                                std::thread::hardware_concurrency(),
                            size_t niceness = 0);
        ~ThreadPool() noexcept;
        ThreadPool(const ThreadPool &) = delete;
        ThreadPool &operator=(const ThreadPool &) = delete;
        void Add(std::shared_ptr<Task> function, PRIORITY pr);
        void Run() noexcept;
        void Pause() noexcept; // stops pulling tasks from queue
        void Stop() noexcept;  // Pause + flush for task queue
        void SetNumberOfThreads(size_t n_threads);
        // void Remove(std::shared_ptr<Task> function); <<----- (ADVANCED)

    private:
        class Compare_Functor
        {
        public:
            bool operator()(const std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> &lhs,
                            const std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY> &rhs) const;
        };

        Waitable_Queue<std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY>,
                       PQ_Wrapper<std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY>,
                                  std::vector<std::pair<std::shared_ptr<Task>, MANAGER_PRIORITY>>, Compare_Functor>>
            m_task_queue;
        std::shared_ptr<Task> m_kill_thread_task;

        std::list<std::unique_ptr<ThreadUnit>> m_thread_queue;
        size_t m_niceness;
        std::mutex modify_threads_q_lock;

        void Manager_Add(std::shared_ptr<Task> function, MANAGER_PRIORITY pr);

        // nested class

        class ThreadUnit
        {
        public:
            explicit ThreadUnit(ThreadPool *m_thread_pool);
            ~ThreadUnit();
            ThreadUnit(const ThreadUnit &) = delete;
            ThreadUnit operator=(const ThreadUnit &) = delete;

            THREAD_STATUS GetStatus();
            void SetStatus(THREAD_STATUS status);

        private:
            void ThreadFunc();
            ThreadPool *m_thread_pool;
            std::atomic<THREAD_STATUS> m_thred_status;
            bool m_is_exit;
            std::thread m_thread;
        };
    };

    class Task
    {
    public:
        void virtual operator()() = 0;
        virtual ~Task();

    private:
    };

    class Default_Task : public Task
    {
    public:
        Default_Task(std::function<void()> func);
        virtual ~Default_Task();
        void virtual operator()();

    private:
        std::function<void()> m_func;
    };
} // namespace ilrd

#endif //__RD12123_THREAD_POOL_HPP__