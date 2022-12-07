/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#include "board.hpp"

#include <unistd.h> // sleep

int main()
{
    const int screenWidth = SQUAR_SIDE * SQUAR_IN_BOARD_SIDE;
    const int screenHeight = SQUAR_SIDE * SQUAR_IN_BOARD_SIDE;
    Camera2D camera;

    InitWindow(screenWidth, screenHeight, "Snake By Daniel Jenudi");
    SetTargetFPS(10);
    BeginMode2D(camera);

    BeginDrawing();

    Board board;
    board.Draw(RED, BLUE);

    EndDrawing();

    sleep(2);

    EndMode2D();

    return 0;
}
