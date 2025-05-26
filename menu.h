#ifndef MENU_H
#define MENU_H

#include "game.h"

void draw_menu(GAME_STATE *state);

void draw_instructions(GAME_STATE *state);

void handle_menu_input(GAME_STATE *state);

void load_highscores();

void save_highscores();

void update_highscores(int new_score);

void draw_highscores(GAME_STATE *state);

void draw_congrats_if_milestone(int score, int milestone, int screenWidth, int screenHeight);

void draw_settings(GAME_STATE *state, float *volume);

#endif