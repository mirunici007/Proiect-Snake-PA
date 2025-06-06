#ifndef MENU_H
#define MENU_H

#include "game.h"
#include <raylib.h>

// External variables that need to be visible to menu functions
extern THEME currentTheme;
extern Color buttonColor;
extern Color textColor;
extern void updateColorsBasedOnTheme(void);

// Menu functions
void draw_menu(GAME_STATE *state);
void draw_instructions(GAME_STATE *state);
void handle_menu_input(GAME_STATE *state);
void draw_congrats_if_milestone(int score, int milestone, int screenWidth, int screenHeight);
void draw_settings(GAME_STATE *state, float *volume);

#endif