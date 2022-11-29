#include <iostream> /* cin, cout, queue, map, string */
#include <queue>    /* queue */
#include <string>   /* string */
#include <map>      /* map */

#include "std_containers.hpp"

using namespace std;

static void Print(queue<string> &str_queue, map<string, size_t> &count_map);

void Histo()
{
    string str = "";
    queue<string> str_queue;
    map<string, size_t> count_map;

    std::getline(std::cin, str);
    while (str.compare("."))
    {
        if (count_map.end() != count_map.find(str))
        {
            ++count_map[str];
        }
        else
        {
            count_map[str] = 1;
            str_queue.push(str);
        }

        std::getline(std::cin, str);
    }

    Print(str_queue, count_map);
}

static void Print(queue<string> &str_queue, map<string, size_t> &count_map)
{
    while (!str_queue.empty())
    {
        std::cout << str_queue.front() << " - count: "
                  << count_map[str_queue.front()] << std::endl;
        str_queue.pop();
    }
}