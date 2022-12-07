/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#include "board.hpp"

Board::Board(size_t n_squar_width, size_t n_squar_hight)
    : m_hight(n_squar_hight), m_width(n_squar_width)
{
    m_board = new Squar *[m_width];

    for (size_t width = 0; width < m_width; ++width)
    {
        m_board[width] = new Squar[m_hight];
    }

    for (size_t hight = 0; hight < m_hight; ++hight)
    {
        for (size_t width = 0; width < m_width; ++width)
        {
            m_board[hight][width].SetLocation(hight, width);
        }
    }
}

Board::~Board()
{
    for (size_t width = 0; width < m_width; ++width)
    {
        delete[] m_board[width];
    }

    delete[] m_board;
}

void Board::Draw(Color color1, Color color2)
{

    Color color_lut[2];
    int which_color = 0;

    color_lut[0] = color1;
    color_lut[1] = color2;

    for (size_t hight = 0; hight < m_hight; ++hight)
    {
        if (0 == ((m_hight * m_width) % 2))
        {
            which_color = !which_color;
        }

        for (size_t width = 0; width < m_width; ++width)
        {
            m_board[hight][width].Draw(color_lut[which_color]);
            which_color = !which_color;
        }
    }
}

Squar *Board::GetSquar(size_t x, size_t y)
{
    return &m_board[x][y];
}
