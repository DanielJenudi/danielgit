#include <list> //list

#include "shapes.hpp"

using namespace std;
using namespace ilrd;

static void PrintShapes(list<Shape *> shapes_list);

int main()
{
    list<Shape *> shapes_list;

    Line l[4];
    Square s[4];
    Rectangle r[4];
    Circle c[4];

    for (size_t i = 0; i < 4; ++i)
    {
        shapes_list.push_back(&l[i]);
        shapes_list.push_back(&s[i]);
        shapes_list.push_back(&r[i]);
        shapes_list.push_back(&c[i]);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        l[i].Move(i * 10);
        s[i].Move(i * 10);
        r[i].Move(i * 10);
        c[i].Move(i * 10);
    }

    PrintShapes(shapes_list);

    return 0;
}

static void PrintShapes(list<Shape *> shapes_list)
{
    std::list<Shape *>::iterator runner = shapes_list.begin();

    while (shapes_list.end() != runner)
    {
        (*runner)->Draw();
        ++runner;
    }
}