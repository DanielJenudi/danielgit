#include <list>     //list
#include <iostream> // cout

using namespace std;

void ReorderList(list<int> *list_to_order);
static void PrintList(list<int> *list_of_nums);

int main()
{
    // 0, 4, 6, 2, 7, 8, 5, 10, 13, 15

    list<int> list1;
    list1.push_back(0);
    list1.push_back(4);
    list1.push_back(6);
    list1.push_back(2);
    list1.push_back(7);
    list1.push_back(8);
    list1.push_back(5);
    list1.push_back(10);
    list1.push_back(13);
    list1.push_back(15);

    ReorderList(&list1);
    PrintList(&list1);

    // 7, 5, 13, 15, 0, 4, 6, 2, 8, 10

    return 0;
}

void ReorderList(list<int> *list_to_order)
{
    list<int> odd_list;
    list<int>::iterator runner = (*list_to_order).begin();

    while (runner != (*list_to_order).end())
    {
        if (0 == ((*runner) % 2))
        {
            odd_list.push_back(*runner);

            list<int>::iterator to_remove = runner;
            ++runner;

            (*list_to_order).erase(to_remove);
        }
        else
        {
            ++runner;
        }
    }

    while (false == odd_list.empty())
    {
        (*list_to_order).push_back(odd_list.front());
        odd_list.pop_front();
    }
}

static void PrintList(list<int> *list_of_nums)
{
    list<int>::iterator runner = (*list_of_nums).begin();

    while (runner != (*list_of_nums).end())
    {
        std::cout << (*runner) << std::endl;
        ++runner;
    }
}