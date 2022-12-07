/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#ifndef __GROE_TOKEN_H__
#define __GROE_TOKEN_H__

#include <cstdlib> // size_t

#include "raylib.h"
#include "squar.hpp"
#include "board.hpp"

class GrowToken
{
public:
    GrowToken(Board *bord);
    void ReSpawn();
    void Draw();

private:
    Squar *m_token;
    Board *m_board;
    size_t m_score;
};

#endif /*__GROE_TOKEN_H__*/
