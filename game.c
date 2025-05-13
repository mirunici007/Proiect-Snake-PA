#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "question.h"
#include "snake.h"

//external variables

#define CELL_SIZE 20 

// Initializes the game with initial values (score, positions, etc.)
void init_game(SNAKE **snake, int *score)
{
    *snake = create_snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    *score = 0;

    srand(time(NULL)); // seed random number generator
}

//updates the game(state, position, score, etc.)
void update_game(SNAKE *snake, int *score, GAME_STATE *state, int *food_x, int *food_y)
{
    Rectangle pausebutton = {SCREEN_WIDTH - 110, 10, 100, 40};

    if (IsKeyPressed(KEY_P) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), pausebutton)))
    {
        if (*state == STATE_RUNNING)
        {
            *state = STATE_PAUSED;
        }
        else if (*state == STATE_PAUSED)
        {
            *state = STATE_RUNNING;
        }
    }

    if(*state == STATE_RUNNING)
    {
        move_snake(snake, *food_x, *food_y);

        //check for food collision 
        if(check_food_collision(snake, *food_x, *food_y))
        {
            *state = STATE_QUESTION;

            //load a random question
            char question[256];
            char correct_answer;
            //load_random_question(question, correct_answer);

            //ask the questions and get the player's answer
            printf("QUESTION:\n%s", question);
            char player_answer;
            printf("YOUR ANSWER: ");
            scanf("%c", &player_answer);

            //validate the player's answer
            // int result = validate_answer(player_answer, correct_answer);
            // apply_question_result(snake, score, result);
            //generate_food(snake, food_x, food_y);
            *state = STATE_RUNNING;
        }

        //check for collision
        if(check_collisions(snake))
        {
            *state = STATE_GAME_OVER;
            printf("Game over! Final score: %d\n", *score);
            return;
        }
    }
}

//resets game after Game Over
void reset_game(SNAKE **snake, int *score)
{
    free_snake(*snake);

    *snake = create_snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // CREATE A NEW SNAKE
    *score = 0; //reset the score

}

int check_collisions(SNAKE *snake)
{
    if (check_self_collision(snake))
    {
        return 1; //the snake collided with itself
    }
    if(check_boundary_collision(snake, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        return 1; //the snake collided with the boundaries
    }

    return 0; //no collision
}

void draw_pause_page()
{

    DrawRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 120, LIGHTGRAY); // Fundalul ferestrei
    DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 60) / 2, SCREEN_HEIGHT / 2 - 20, 60, BLACK);        
    DrawText("Press P to Resume", SCREEN_WIDTH / 2 - MeasureText("Press P to Resume", 20) / 2, SCREEN_HEIGHT / 2 + 35, 20, DARKGRAY); 

    int margin = 20;
    int size = 20;

    Vector2 v1 = {SCREEN_WIDTH - margin - size, margin};
    Vector2 v2 = {SCREEN_WIDTH - margin, margin + size / 2};
    Vector2 v3 = {SCREEN_WIDTH - margin - size, margin + size};

    DrawTriangle(v1, v2, v3, RED);
    DrawLineV(v1, v2, RED);
    DrawLineV(v2, v3, RED);
    DrawLineV(v3, v1, RED);

}

void draw_pause_button()
{
    int bar_width = 10;
    int bar_height = 20;
    int bar_spacing = 5;
    int bar_x = SCREEN_WIDTH - 90;
    int bar_y = 20;

    DrawRectangle(bar_x, bar_y, bar_width, bar_height, DARKGREEN);
    DrawRectangle(bar_x + bar_width + bar_spacing, bar_y, bar_width, bar_height, DARKGREEN);
}
