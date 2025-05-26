#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"

// screen size
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

//external variables
extern int score;
extern Color feedbackColor;

typedef enum{
    STATE_START_PAGE,
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_QUESTION,
    STATE_HIGHSCORES,
    STATE_GAME_OVER,
    STATE_SETTINGS // <-- adaugă acest state nou
} GAME_STATE;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct {
    GAME_STATE state;
    Direction dir;
    // add other fields like score, snake, etc.
} Game;

//function declarations

//initializes the score to 0
void init_game(SNAKE **snake, int *score);

// Updates the game state (movement, collisions, etc.)
void update_game(SNAKE *snake, int *score, GAME_STATE *state, FOOD *food);

// Resets the game after Game Over
void reset_game(SNAKE **snake, int *score);

// Checks for collisions (self-collision or boundary collision)
int check_collisions(SNAKE *snake);

// Applies the result of a question (score changes, game state updates, etc.)
 //void apply_question_result(SNAKE *snake, int *score, int result);

// // Generates food at a random position
// void generate_food(SNAKE *snake, int *food_x, int *food_y);

// // Renders the game state (snake, food, score, etc.)
void draw_pause_page();

void draw_pause_button();

// // Handles user input for controlling the snake
void handle_input(SNAKE *snake, GAME_STATE *state, int *score);

void validate_answer(int result, int* score, SNAKE* snake, FOOD* food);

#endif // GAME_H