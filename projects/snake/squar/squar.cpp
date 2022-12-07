#include "squar.hpp"

/*** Squar ***/
Squar::Squar(size_t x, size_t y, size_t width, size_t height)
    : m_content(NOTHING)
{
    m_rec.x = x * SQUAR_SIDE;
    m_rec.y = y * SQUAR_SIDE;
    m_rec.width = width;
    m_rec.height = height;
}
void Squar::Draw(Color color)
{
    DrawRectangleRec(m_rec, color);
}

void Squar::SetLocation(size_t x, size_t y)
{
    m_rec.x = x * SQUAR_SIDE;
    m_rec.y = y * SQUAR_SIDE;
}

size_t Squar::GetLocationX()
{
    return (m_rec.x / SQUAR_SIDE);
}

size_t Squar::GetLocationY()
{
    return (m_rec.y / SQUAR_SIDE);
}

Squar_Content Squar::GetContent()
{
    return m_content;
}
void Squar::SetContent(Squar_Content new_content)
{
    m_content = new_content;
}
