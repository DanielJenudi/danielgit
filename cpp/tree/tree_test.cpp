/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 14/08/22
- Reviewed By: Moshe Schreiber
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "file.hpp"
#include "directory.hpp"
#include "tree.hpp"

#include <string>
#include <dirent.h>
#include <iostream>

using namespace ilrd;

int main()
{
    /*     DIR *dir = opendir("/home");
        struct dirent *d_list = readdir(dir);
        std::string path = "hello/yaniv";
        std::string m_name;

        while (d_list != 0)
        {

            std::cout << d_list->d_name << std::endl;
            d_list = readdir(dir);
        }

        size_t last_index = 0;

        last_index = path.find_last_of("/");
        m_name = path.substr(last_index + 1);

        std::cout << m_name << std::endl; */

    try
    {
        Tree tree("/home/daniel/git/cpp");
        tree.Display();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}