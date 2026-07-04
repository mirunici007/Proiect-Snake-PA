#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>   //for getch()
#include "game.h"    //for GAME struct
#include "input.h"
#include "question.h"  //for currentQuestion

void handle_game_input(Game* game)
{
    int ch = getch();

    switch (ch)
    {
    case KEY_UP:
        if (game->dir != DIR_DOWN) game->dir = DIR_UP;
        break;
    case KEY_DOWN:
        if (game->dir != DIR_UP) game->dir = DIR_DOWN;
        break;
    case KEY_LEFT:
        if (game->dir != DIR_RIGHT) game->dir = DIR_LEFT;
        break;
    case KEY_RIGHT:
        if (game->dir != DIR_LEFT) game->dir = DIR_RIGHT;
        break;
    }
}

int handle_input_text()
{
    int ch = getch();  //waits for user input and returns the ASCII value of the pressed key

    switch (ch)
    {
    case '1':
    case 'a':
    case 'A':
        return 0;
    case '2':
    case 'b':
    case 'B':
        return 1;
    case '3':
    case 'c':
    case 'C':
        return 2;
    case '4':
    case 'd':
    case 'D':
        return 3;
    default:
        return -1; //invalid input
    }
}
