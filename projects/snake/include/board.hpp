/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include <cstdlib> // size_t

#include "raylib.h"
#include "board.hpp"
#include "squar.hpp"

#define SQUAR_IN_BOARD_SIDE (10)

class Board
{
public:
    Board(size_t n_squar_width = SQUAR_IN_BOARD_SIDE, size_t n_squar_hight = SQUAR_IN_BOARD_SIDE);
    ~Board();
    void Draw(Color color1, Color color2);
    Squar *GetSquar(size_t x, size_t y);

private:
    Squar **m_board;
    size_t m_hight;
    size_t m_width;
};

#endif /*__BOARD_H__*/
