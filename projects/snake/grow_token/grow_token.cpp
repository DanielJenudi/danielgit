/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#include <exception> //runtime_error
#include <stdexcept> //runtime_error

#include "grow_token.hpp"

GrowToken::GrowToken(Board *board)
    : m_board(board), m_score(0)
{
    m_token = board->GetSquar(std::rand() % SQUAR_IN_BOARD_SIDE,
                              std::rand() % SQUAR_IN_BOARD_SIDE);

    this->ReSpawn();
}

void GrowToken::ReSpawn()
{
    if (m_score == ((SQUAR_IN_BOARD_SIDE * SQUAR_IN_BOARD_SIDE) - 5))
    {
        throw std::runtime_error("WIN");
    }

    size_t new_x = std::rand() % SQUAR_IN_BOARD_SIDE;
    size_t new_y = std::rand() % SQUAR_IN_BOARD_SIDE;

    for (size_t i = new_x; true; i = ((i + 1) % SQUAR_IN_BOARD_SIDE))
    {
        for (size_t j = new_y; true; j = ((j + 1) % SQUAR_IN_BOARD_SIDE))
        {
            if (NOTHING == m_board->GetSquar(i, j)->GetContent())
            {
                m_token = m_board->GetSquar(i, j);
                m_token->SetContent(GROW_TOKEN);
                ++m_score;
                return;
            }
        }
    }
}

void GrowToken::Draw()
{
    m_token->Draw(GREEN);
}