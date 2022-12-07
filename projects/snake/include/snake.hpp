/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <cstdlib> // size_t
#include <list>    // list

#include "raylib.h"
#include "squar.hpp"
#include "board.hpp"
#include "grow_token.hpp"

#define SNAKE_START_SIZE (2)
#define SNAKE_START_X (4)
#define SNAKE_START_Y (4)

enum Direction
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
public:
    Snake(Board *board, size_t start_size = SNAKE_START_SIZE, Direction start_direction = LEFT,
          size_t start_x = SNAKE_START_X, size_t start_y = SNAKE_START_Y,
          Color snake_color = BLACK);
    void SetDirection(Direction new_direction);
    void Move(void);
    void Draw(void);

private:
    std::list<Squar *> m_snake;
    Board *m_board;
    GrowToken m_token;

    Direction m_direction;
    Color m_color;
};

#endif /*__SNAKE_H__*/
