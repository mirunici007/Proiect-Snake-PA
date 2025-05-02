#include <stdio.h>
#include <stdlib.h>

#include "question.h"
#include "game.h"
#include "input.h"
#include "raylib.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

//declaring the variables

typedef enum
{
    STATE_RUNNING,
    STATE_QUESTION,
    STATE_GAME_OVER
}GAME_STATE;

int main()
{
    const int screen_width = SCREEN_WIDTH;
    const int screen_height = SCREEN_HEIGHT;

    InitWindow(screen_width, screen_height, "Snake Quiz Game");
    Set

    init_game();

    GAME_STATE state = STATE_RUNNING;
    char currentAnswer[2]="";


    switch(state){
        case STATE_RUNNING:     handle_input();
                                update_game(&state);
                                draw_game();
                                break;

        case STATE_QUESTION:    handle_text_input(currentAnswer, sizeof(currentAnswer));
                                draw_text("Choose the answer: ", 100, 200, 20, BLACK);
                                draw_text(currentAnswer, 100, 230, 20, DARKBLUE);
                                draw_text("Press ENTER to validate your answer.", 100, 270, 20, RED);
                                
                                if()
                                {
                                    if(validate_answer(currentAnswer))
                                    {
                                        question_result(true);
                                    }
                                    else
                                    {
                                        question_result(false);
                                    }

                                    currentAnswer[0] = '\0';
                                    state = STATE_RUNNING;
                                }

                                break;

        case STATE_GAME_OVER:   draw_text("GAME OVER!", 300, 250, 50, RED);
                                draw_text("Press R to restart the game.", 270, 300, 20, GRAY);

                                if(pressed(KEY_R))
                                {
                                    reset_game();
                                    state = STATE_RUNNING;
                                }

                                break;
    }

    end_drawing();
}

//init_game(), update_game(), reset_game(), apply_question_result() - game.c.
//handle_input() și handle_text_input() - input.c
//validate_answer() - question.c