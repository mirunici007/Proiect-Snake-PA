// #ifndef GAME_H
// #define GAME_H

// #include "snake.h"

// // screen size
// #define SCREEN_WIDTH 1000
// #define SCREEN_HEIGHT 700

// //external variables
// extern int score;

// typedef enum{
//     STATE_RUNNING,      //game running
//     STATE_QUESTION,     //game paused for a wuestion
//     STATE_PAUSE,        //game paused
//     STATE_MENU,         //game menu
//     STATE_GAME_OVER     //game over
// }GAME_STATE;

// //function declarations

// //initializes the score to 0
// void init_game(SNAKE **snake, int *score);

// // Updates the game state (movement, collisions, etc.)
// void update_game(SNAKE *snake, int *score, GAME_STATE *state, int *food_x, int *food_y);

// // Resets the game after Game Over
// void reset_game(SNAKE **snake, int *score);

// // Checks for collisions (self-collision or boundary collision)
// int check_collisions(SNAKE *snake);

// // Applies the result of a question (score changes, game state updates, etc.)
// void apply_question_result(SNAKE *snake, int *score, int result);

// // Generates food at a random position
// void generate_food(SNAKE *snake, int *food_x, int *food_y);

// // Renders the game state (snake, food, score, etc.)
// void render_game(SNAKE *snake, int food_x, int food_y, int score);

// // Handles user input for controlling the snake
// void handle_input(SNAKE *snake, GAME_STATE *state);

// #endif // GAME_H