#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include <raylib.h>

//screen size
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

//enumeration of the theme types
typedef enum {
    THEME_LIGHT,
    THEME_DARK
} THEME;

//external variables
extern int score;
extern Color feedbackColor;
extern char feedbackMessage[64];
extern float feedbackTimer;
extern THEME currentTheme;
extern Color bgColor;
extern Color textColor;
extern Color buttonColor;
extern Color menuButtonColor;
extern bool hitWallFrame;

//enumeration for the game states
typedef enum{
    STATE_START_PAGE,
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_QUESTION,
    STATE_GAME_OVER,
    STATE_SETTINGS,
    STATE_GAME_MODE
} GAME_STATE;

//enumeration for the snake's direction
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef enum{
    CLASSIC = 0,
    WALLS_WRAP = 1
}GAME_MODE;

extern GAME_MODE currentGameMode;

//the state of the game, including the snake's direction
typedef struct {
    GAME_STATE state;
    Direction dir;
} Game;

//function declarations
//function to initialize the game,create a new snake and set the score to 0
void init_game(SNAKE **snake, int *score);

//function to update the game state, including moving the snake, checking for collisions and handling user input
void update_game(SNAKE *snake, int *score, GAME_STATE *state, FOOD *food);

//function to reset the game, freeing the current snake and creating a new one and resetting the score to 0
void reset_game(SNAKE **snake, int *score);

//function to check for collisions
int check_collisions(SNAKE *snake);

//functions to draw the pause page and pause button
void draw_pause_page(void);
void draw_pause_button(void);

//functiona to handle user input, including checking for answers to questions and updating the game state accordingly
void handle_input(SNAKE *snake, GAME_STATE *state, int *score);
void validate_answer(int result, int* score, SNAKE* snake, FOOD* food);

//function to update the colors based on the current theme
void updateColorsBasedOnTheme(void);

#endif