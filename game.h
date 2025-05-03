#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

//declare the variables

extern int score;

typedef enum{
    STATE_RUNNING,
    STATE_QUESTION,
    STATE_PAUSE,
    STATE_MENU,
    STATE_GAME_OVER
}GAME_STATE;

//declare the functions

void init_game(int *score){
    *score = 0;
}

void init_snake(SNAKE *snake, int x, int y){
    
}

// 0: up, 1: right, 2: down, 3: left