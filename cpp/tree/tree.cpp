/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 14/08/22
- Reviewed By: Moshe Schreiber
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream> // cout

#include "tree.hpp"

namespace ilrd
{
    static Directory *InitRoot(const std::string &path);

    Tree::Tree(const std::string &path) : m_root(InitRoot(path))
    {
        // empty
    }

    Tree::~Tree() noexcept
    {
        delete m_root;
    }

    void Tree::Display()
    {
        m_root->print();
    }

    static Directory *InitRoot(const std::string &path)
    {
        Directory *d = 0;
        try
        {
            d = new Directory(path);
        }
        catch (const std::exception &e)
        {
            delete d;
            std::cerr << e.what() << '\n';
            throw(e);
        }

        return d;
    }
}
