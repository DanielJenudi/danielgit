/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#include <cstring>  // strcmp
#include <unistd.h> // sleep
#include <thread>

#include "snake.hpp"
#include "board.hpp"
#include "grow_token.hpp"

#include "raylib.h"
#include "raymath.h"

int main()
{
    const int screenWidth = SQUAR_SIDE * SQUAR_IN_BOARD_SIDE;
    const int screenHeight = SQUAR_SIDE * SQUAR_IN_BOARD_SIDE;
    Camera2D camera;

    InitWindow(screenWidth, screenHeight, "Snake By Daniel Jenudi");
    SetTargetFPS(8);

    Board board;
    Snake snake(&board);

    BeginMode2D(camera);

    BeginDrawing();

    board.Draw(RED, BLUE);
    snake.Draw();

    EndDrawing();

    EndMode2D();

    sleep(1);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_LEFT))
        {
            snake.SetDirection(LEFT);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            snake.SetDirection(RIGHT);
        }
        else if (IsKeyDown(KEY_UP))
        {
            snake.SetDirection(UP);
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            snake.SetDirection(DOWN);
        }

        try
        {
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
            snake.Move();
        }
        catch (const std::exception &e)
        {
            if (0 == strcmp(e.what(), "WIN"))
            {
                BeginDrawing();

                ClearBackground(BLACK);
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("WIN!", 100, 100, 100, WHITE);
                // DrawText("FINAL SCORE:", 120, 220, 20, WHITE);

                EndDrawing();

                sleep(3);
                break;
            }
            else if (0 == strcmp(e.what(), "LOSE"))
            {
                BeginDrawing();

                ClearBackground(BLACK);
                DrawRectangle(0, 0, screenWidth, screenHeight, RED);
                DrawText("LOSE!", 100, 100, 100, WHITE);
                // DrawText("FINAL SCORE:", 120, 220, 20, WHITE);

                EndDrawing();

                sleep(2);
                break;
            }
        }

        BeginMode2D(camera);

        BeginDrawing();

        board.Draw(RED, BLUE);
        snake.Draw();

        EndDrawing();

        EndMode2D();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}