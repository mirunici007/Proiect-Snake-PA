#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "question.h"

//external variables
int score; // initialize the score

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
            generate_food(snake, food_x, food_y);
            *state = STATE_RUNNING;
        }

        //check for collision
        if(check_collisions(snake))
        {
            *state = STATE_GAME_OVER;
            printf("Game over! Final score: %d\n", *score);
        }
    }
}

//resets game after Game Over
void reset_game(SNAKE **snake, int *score)
{
    free_snake(*snake);

    *snake = create_snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) // CREATE A NEW SNAKE
    *score = 0; //reset the score
}