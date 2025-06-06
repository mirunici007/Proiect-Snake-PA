#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include <raylib.h>

// screen size
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

// Theme definitions
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

typedef enum{
    STATE_START_PAGE,
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_QUESTION,
    STATE_GAME_OVER,
    STATE_SETTINGS
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
} Game;

// Function declarations
void init_game(SNAKE **snake, int *score);
void update_game(SNAKE *snake, int *score, GAME_STATE *state, FOOD *food);
void reset_game(SNAKE **snake, int *score);
int check_collisions(SNAKE *snake);
void draw_pause_page(void);
void draw_pause_button(void);
void handle_input(SNAKE *snake, GAME_STATE *state, int *score);
void validate_answer(int result, int* score, SNAKE* snake, FOOD* food);
void updateColorsBasedOnTheme(void);

#endif // GAME_H