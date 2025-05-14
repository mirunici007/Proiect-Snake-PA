#include "raylib.h"
#include "menu.h"
#include "game.h"

void draw_menu(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText ("Snake Game - MENU", width / 2 - MeasureText("Snake Game - MENU", 40) / 2, height / 2 - 100, 40, GREEN);

    Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
    Rectangle back_to_start_page = {width / 2 - 150, 390, 300, 50};

    DrawRectangleRec(instructions_button, DARKBLUE);
    DrawText("Instructions", instructions_button.x + instructions_button.width / 2 - MeasureText("Instructions", 20) / 2, instructions_button.y + 15, 20, RAYWHITE);

    DrawRectangleRec( back_to_start_page, RED);
    DrawText("Back to Start Page",  back_to_start_page.x +  back_to_start_page.width / 2 - MeasureText("Back to Start Page", 20) / 2,  back_to_start_page.y + 15, 20, RAYWHITE);
}

void draw_instructions(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Instructions", width / 2 - MeasureText("Instructions", 40) / 2, height / 2 - 100, 40, GREEN);
    DrawText("Use W,S,A,D to control the snake", width / 2 - MeasureText("Use W,S,A,D to control the snake", 20) / 2, height / 2 - 50, 20, WHITE);
    DrawText("Eat the food and answer the questions correctly to grow the snake", width / 2 - MeasureText("Eat the food and answer the questions correctly to grow the snake", 20) / 2, height / 2, 20, WHITE);
    DrawText("Avoid the walls and the snake's body", width / 2 - MeasureText("Avoid the walls and the snake's body", 20) / 2, height / 2 + 50, 20, WHITE);

    Rectangle back_button = {width / 2 - 75, height / 2 + 100, 150, 40};
    DrawRectangleRec(back_button, DARKBLUE);
    DrawText("Back to Menu", back_button.x + back_button.width / 2 - MeasureText("Back to Menu", 20) / 2, back_button.y + 10, 20, RAYWHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), back_button))
    {
        *state = STATE_MENU;
    }
}

void handle_menu_input(GAME_STATE *state, SNAKE **snake, int *food_x, int *food_y, int *score)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
        if (CheckCollisionPointRec(mouse, instructions_button))
        {
            *state = STATE_INSTRUCTIONS;  
        }

        Rectangle back_to_start_page = {width / 2 - 150, 390, 300, 50};
        if (CheckCollisionPointRec(mouse, back_to_start_page))
        {
            *state = STATE_START_PAGE;  
        }
    }
}
        