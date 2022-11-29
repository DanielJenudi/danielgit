/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 13/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <fstream>  // fstream
#include <iostream> // ios_base
#include <memory>   // shared ptr
#include <ctime>    // time_t

#include "logger.hpp"
#include "thread_pool.hpp"

using namespace ilrd;

/***** Logger_Task *****/

class Logger_Task : public Task
{
public:
    Logger_Task(const time_t &time_of_log, const std::string &path,
                const std::string massage);
    virtual ~Logger_Task();
    void virtual operator()();

private:
    const time_t m_time_of_log;
    const std::string m_path;
    const std::string m_massage;
};

Logger_Task::Logger_Task(const time_t &time_of_log, const std::string &path,
                         const std::string massage)
    : m_time_of_log(time_of_log), m_path(path), m_massage(massage)
{
    // empty
}

Logger_Task::~Logger_Task()
{
    // empty
}

void Logger_Task::operator()()
{

    std::fstream logger_file;
    logger_file.open(m_path, std::ios_base::in | std::fstream::app);

    std::tm *timeinfo = std::localtime(&m_time_of_log);

    char buffer[20];
    std::strftime(buffer, 20, "%d.%m.%Y %H:%M:%S", timeinfo);

    logger_file << "*" << buffer << "* : " << m_massage << "\n";

    logger_file.close();
}

/***** Logger *****/

Logger::Logger(const std::string &path)
    : m_thread_pool(1), m_path(path)
{
    time(nullptr);
    m_thread_pool.Run();
}

void Logger::Log(const std::string &log)
{
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    m_thread_pool.Add(std::shared_ptr<Task>(new Logger_Task(now, m_path, log)), HIGH);
}

void Logger::SetPath(const std::string &path)
{
    m_path = path;
}
