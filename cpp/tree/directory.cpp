/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 14/08/22
- Reviewed By: Moshe Schreiber
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>    // cout
#include <dirent.h>    // DIR
#include <sys/types.h> //struct dirent
#include <cstring>     // strcmp

#include "directory.hpp"
#include "reg_file.hpp"

#define BLUE "\033[34m"
#define WHITE "\033[37m"

namespace ilrd
{
    static void ClearList(std::list<File *> d_list);

    Directory::Directory(const std::string &path) : m_name(path.substr(path.find_last_of("/") + 1))
    {
        DIR *dir = opendir(path.data());
        if (0 == dir)
        {
            return;
        }

        struct dirent *d_list = readdir(dir);

        while (0 != d_list)
        {

            if (0 == strcmp(".", d_list->d_name) ||
                0 == strcmp("..", d_list->d_name))
            {
                d_list = readdir(dir);
                continue;
            }

            if (DT_DIR == d_list->d_type)
            {
                Directory *d = 0;
                try
                {
                    d = new Directory(path + "/" + d_list->d_name);
                    m_dir_files.push_back(d);
                }
                catch (const std::exception &e)
                {
                    delete d;
                    d = 0;

                    ClearList(m_dir_files);

                    std::cerr << e.what() << '\n';
                    throw(e);
                }
            }
            else
            {
                Reg_File *rf = 0;
                try
                {
                    if (0 == strcmp("file.cpp", d_list->d_name))
                    {
                        std::bad_alloc ba;
                        throw(ba);
                    }
                    rf = new Reg_File(d_list->d_name);
                    m_dir_files.push_back(rf);
                }
                catch (const std::exception &e)
                {
                    delete rf;
                    rf = 0;

                    ClearList(m_dir_files);

                    std::cerr << e.what() << '\n';
                    throw(e);
                }
            }

            d_list = readdir(dir);
        }

        closedir(dir);
    }

    Directory::~Directory() noexcept
    {
        std::cout << m_name << std::endl;
        ClearList(m_dir_files);
    }

    void Directory::print(size_t indents)
    {
        for (size_t i = 0; i < indents; ++i)
        {
            std::cout << " ";
        }

        std::cout << BLUE << m_name << "/" << WHITE << std::endl;

        for (std::list<File *>::iterator runner = m_dir_files.begin();
             runner != m_dir_files.end(); ++runner)
        {
            (*runner)->print(indents + m_name.length());
        }
    }

    static void ClearList(std::list<File *> d_list)
    {
        while (false == d_list.empty())
        {
            delete d_list.front();
            d_list.pop_front();
        }
    }
}