/*****************************************************************************
 *Author: Daniel Jenudi
 *Reviewer: Yariv
 *Date: 07.09.22
 ******************************************************************************/

#include <thread>
#include <string>
#include <iostream>

#include "waitable_queue.hpp"

using namespace std;
using namespace ilrd;

Waitable_Queue<string> wq;
std::mutex g_lock;

void Write(string msg)
{
    wq.Push(msg);
}

void Read()
{
    string str;
    wq.Pop(str);

    g_lock.lock();
    cout << "Read: " << str;
    g_lock.unlock();
}

void ReadWaitMil()
{
    const chrono::milliseconds t(10);
    string str = "TIME REACH OUT\n";
    wq.Pop(str, t);

    g_lock.lock();
    cout << "Mil Read Status " << str;
    g_lock.unlock();
}

void ReadWaitSec()
{
    const chrono::seconds t(3);
    string str = "TIME REACH OUT\n";
    wq.Pop(str, t);

    g_lock.lock();
    cout << "Sec Read Status: " << str;
    g_lock.unlock();
}

int main()
{
    thread t1(Write, "ONE\n");
    thread t2(Write, "TWO\n");
    thread t3(Read);
    thread t4(Read);
    thread t5(Write, "THREE\n");
    thread t6(Read);

    while (!wq.IsEmpty())
    {
    }

    thread t7(ReadWaitMil);
    thread t8(ReadWaitSec);

    cout << wq.IsEmpty() << "\n";

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return 0;
}