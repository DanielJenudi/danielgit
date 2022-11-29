#include <iostream> // cout

#include "shapes.hpp"

namespace ilrd
{
    /******* Shape *******/

    Shape::Shape() : m_offset(0)
    {
        // empty
    }

    Shape::~Shape()
    {
        // empty
    }

    void Shape::Draw() const
    {
        for (size_t i = 0; i < m_offset; ++i)
        {
            std::cout << " ";
        }
    }

    void Shape::Move(size_t offset)
    {
        m_offset += offset;
    }

    /******* Line *******/

    void Line::Draw() const
    {
        Shape::Draw();

        std::cout << "Line" << std::endl;
    }

    /******* Circle *******/

    void Circle::Draw() const
    {
        Shape::Draw();

        std::cout << "Circel" << std::endl;
    }

    /******* Rectangle *******/

    void Rectangle::Draw() const
    {
        Shape::Draw();

        std::cout << "Rectangle" << std::endl;
    }

    /******* Square *******/

    void Square::Draw() const
    {
        Shape::Draw();

        std::cout << "Square" << std::endl;
    }

}