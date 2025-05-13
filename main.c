#include "raylib.h"
#include "snake.h"
#include "game.h"
#include <stddef.h>

int score = 0;

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(10);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetExitKey(KEY_NULL);  // ESC NU mai închide aplicația automat

    GAME_STATE state = STATE_MENU;

    SNAKE *snake = NULL;
    int food_x = 0;
    int food_y = 0;

    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(BLACK);

        // ------------------ MENU ------------------
        if (state == STATE_MENU)
        {
            DrawText("Snake Game", currentWidth / 2 - 100, 100, 40, GREEN);

            Rectangle startBtn = {currentWidth / 2 - 100, 250, 200, 50};
            Rectangle menuBtn  = {currentWidth / 2 - 100, 320, 200, 50};

            DrawRectangleRec(startBtn, DARKGREEN);
            DrawText("START", startBtn.x + 60, startBtn.y + 15, 20, RAYWHITE);

            DrawRectangleRec(menuBtn, DARKBLUE);
            DrawText("MENIU", menuBtn.x + 60, menuBtn.y + 15, 20, RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startBtn))
                {
                    int midX = currentWidth / 2;
                    int midY = currentHeight / 2;

                    snake = create_snake((midX / 20), (midY / 20));
                    for (int i = 0; i < 10; i++) grow_snake(snake);

                    food_x = GetRandomValue(0, 39) * 20;
                    food_y = GetRandomValue(0, 22) * 20;
                    score = 0;
                    state = STATE_RUNNING;
                }
                if (CheckCollisionPointRec(mouse, menuBtn))
                {
                    state = STATE_QUESTION;
                }
            }
        }

        // ------------------ "NEATA" ------------------
        else if (state == STATE_QUESTION)
        {
            DrawText("neata", currentWidth / 2 - 50, currentHeight / 2 - 20, 40, YELLOW);
            DrawText("Apasa ESC pentru a reveni", currentWidth / 2 - 120, currentHeight / 2 + 40, 20, GRAY);

            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = STATE_MENU;
            }
        }

        // ------------------ GAME ------------------
        else if (state == STATE_RUNNING)
        {
            // Comută între pauză și continuare joc la apăsarea tastei P
            if (IsKeyPressed(KEY_P))
            {
                state = STATE_PAUSED;  // Pune jocul pe pauză
            }

            if (IsKeyPressed(KEY_W) && snake->direction != DOWN) set_snake_direction(snake, UP);
            if (IsKeyPressed(KEY_S) && snake->direction != UP) set_snake_direction(snake, DOWN);
            if (IsKeyPressed(KEY_A) && snake->direction != RIGHT) set_snake_direction(snake, LEFT);
            if (IsKeyPressed(KEY_D) && snake->direction != LEFT) set_snake_direction(snake, RIGHT);

            move_snake(snake, food_x, food_y);
            update_game(snake, &score, &state, &food_x, &food_y);

            draw_pause_button();
            draw_snake(snake);
        }

        // ------------------ PAUSED ------------------
        else if (state == STATE_PAUSED)
        {
            draw_pause_page();

            Rectangle backBtn = {currentWidth / 2 - 75, currentHeight / 2 + 150, 150, 40};
            DrawRectangleRec(backBtn, GRAY);
            DrawText("Inapoi la meniu", backBtn.x + 10, backBtn.y + 10, 20, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, backBtn))
                {
                    state = STATE_MENU;
                    if (snake != NULL)
                    {
                        free_snake(snake);
                        snake = NULL;
                    }
                }
            }

            // La apăsarea tastei P sau ENTER, jocul se reia
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
            {
                state = STATE_RUNNING;  // Revine în joc
            }
        }

        // ------------------ GAME OVER ------------------
        else if (state == STATE_GAME_OVER)
        {
            DrawText("Game Over", currentWidth / 2 - 60, currentHeight / 2 - 30, 30, RED);
            DrawText("Press R to restart", currentWidth / 2 - 90, currentHeight / 2 + 10, 20, WHITE);
            DrawText("Press ESC to return to menu", currentWidth / 2 - 120, currentHeight / 2 + 40, 20, GRAY);

            if (IsKeyPressed(KEY_R))
            {
                reset_game(&snake, &score);
                for (int i = 0; i < 10; i++) grow_snake(snake);
                food_x = GetRandomValue(0, 39) * 20;
                food_y = GetRandomValue(0, 22) * 20;
                state = STATE_RUNNING;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = STATE_MENU;
                if (snake != NULL)
                {
                    free_snake(snake);
                    snake = NULL;
                }
            }
        }

        EndDrawing();
    }

    if (snake != NULL)
        free_snake(snake);

    CloseWindow();
    return 0;
}
