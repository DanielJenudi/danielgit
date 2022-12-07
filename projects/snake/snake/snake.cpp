/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#include "snake.hpp"
#include "raylib.h"

#include <iostream>

Snake::Snake(Board *board, size_t start_size, Direction start_direction,
             size_t start_x, size_t start_y, Color snake_color)
    : m_board(board), m_token(GrowToken(board)), m_direction(start_direction), m_color(snake_color)
{
    for (size_t i = 0; i < start_size; ++i)
    {
        m_snake.push_front(m_board->GetSquar((start_x - i), start_y));
        m_snake.front()->SetContent(SNAKE);
    }
}
void Snake::Move(void)
{
    size_t new_x = m_snake.front()->GetLocationX();
    size_t new_y = m_snake.front()->GetLocationY();

    switch (m_direction)
    {
    case UP:
        new_y = (0 == new_y) ? throw std::runtime_error("LOSE") : (new_y - 1);
        break;

    case DOWN:
        new_y = ((SQUAR_IN_BOARD_SIDE - 1) == new_y) ? throw std::runtime_error("LOSE") : (new_y + 1);
        break;

    case RIGHT:
        new_x = ((SQUAR_IN_BOARD_SIDE - 1) == new_x) ? throw std::runtime_error("LOSE") : (new_x + 1);
        break;

    case LEFT:
        new_x = (0 == new_x) ? throw std::runtime_error("LOSE") : (new_x - 1);
        break;
    }

    m_snake.push_front(m_board->GetSquar(new_x, new_y));
    m_snake.back()->SetContent(NOTHING);
    m_snake.pop_back();

    if (SNAKE == m_snake.front()->GetContent())
    {
        throw std::runtime_error("LOSE");
    }

    if (GROW_TOKEN == m_snake.front()->GetContent())
    {
        m_snake.front()->SetContent(SNAKE);
        m_snake.push_back(m_snake.back());
        m_token.ReSpawn();
    }
    else
    {
        m_snake.front()->SetContent(SNAKE);
    }
}

void Snake::SetDirection(Direction new_direction)
{
    switch (m_direction)
    {
    case UP:
        if (DOWN == new_direction)
        {
            return;
        }
        break;

    case DOWN:
        if (UP == new_direction)
        {
            return;
        }
        break;

    case RIGHT:
        if (LEFT == new_direction)
        {
            return;
        }
        break;

    case LEFT:
        if (RIGHT == new_direction)
        {
            return;
        }
        break;
    }

    m_direction = new_direction;
}

void Snake::Draw(void)
{
    for (Squar *squar : m_snake)
    {
        squar->Draw(m_color);
    }

    m_token.Draw();
}