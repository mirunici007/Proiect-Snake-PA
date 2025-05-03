#include <stdio.h>
#include <stdlib.h>

#include "question.h"
#include "game.h"
#include "input.h"
#include "raylib.h"


//declaring the variables

int score;

int main()
{
    const int screen_width = SCREEN_WIDTH;
    const int screen_height = SCREEN_HEIGHT;

    InitWindow(screen_width, screen_height, "Snake Quiz Game");
    SetTagetFPS(60);

    init_game(&score);

    GAME_STATE state = STATE_RUNNING;
    char currentAnswer[2]="";

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(state){
            case STATE_RUNNING:     handle_input();
                                    update_game(&state);
                                    draw_game();
                                    break;
    
            case STATE_QUESTION:    handle_text_input(currentAnswer, sizeof(currentAnswer));
                                    DrawText("Choose the answer: ", 100, 200, 20, BLACK);
                                    DrawText(currentAnswer, 100, 230, 20, DARKBLUE);
                                    DrawText("Press ENTER to validate your answer.", 100, 270, 20, RED);
                                    
                                    if(IsKeyPressed(KEY_ENTER))
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
    
            case STATE_GAME_OVER:   DrawText("GAME OVER!", 300, 250, 50, RED);
                                    DrawText("Press R to restart the game.", 270, 300, 20, GRAY);
    
                                    if(IsKeyPressed(KEY_R))
                                    {
                                        reset_game();
                                        state = STATE_RUNNING;
                                    }
    
                                    break;
        }
    
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//init_game(), update_game(), reset_game(), apply_question_result() in game.c.
//handle_input() și handle_text_input() in input.c
//validate_answer() in question.c
//asta e o propunere de implementare, mai schimbam