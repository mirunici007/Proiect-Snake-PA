#include "snake.h"
#include "raylib.h"
#include "game.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(10);

    //create the snake
    SNAKE *snake = create_snake((SCREEN_WIDTH / 2) / 20, (SCREEN_HEIGHT / 2) / 20);

    for(int i = 0; i < 100; i++)
    {
        grow_snake(snake);
    }

    int food_x = (GetRandomValue(0, 39) * 20);
    int food_y = (GetRandomValue(0, 22) * 20);

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_W) && snake->direction != DOWN)
        {
            set_snake_direction(snake, UP);
        }
        if(IsKeyPressed(KEY_S) && snake->direction != UP)
        {
            set_snake_direction(snake, DOWN);
        }
        if(IsKeyPressed(KEY_A) && snake->direction != RIGHT)
        {
            set_snake_direction(snake, LEFT);
        }
        if(IsKeyPressed(KEY_D) && snake->direction != LEFT)
        {
            set_snake_direction(snake, RIGHT);
        }

        //move snake
        move_snake(snake, food_x, food_y);

        //check for collision with food
        /*if(check_food_collision(snake, food_x, food_y))
        {
            //functie pt intrebare
            //fctie pt verificare raspuns
        }*/

        //draw game
        BeginDrawing();

        ClearBackground(BLACK);
        draw_snake(snake);

        // Termină desenarea
        EndDrawing();
    }
    free_snake(snake);
    // Închide fereastra
    CloseWindow();

    return 0;
}