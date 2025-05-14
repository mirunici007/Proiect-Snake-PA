#ifndef MENU_H
#define MENU_H

#include "game.h"

void draw_menu(GAME_STATE *state);

void draw_instructions(GAME_STATE *state);

void handle_menu_input(GAME_STATE *state, SNAKE **snake, int *food_x, int *food_y, int *score);

#endif