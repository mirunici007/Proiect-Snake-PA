#include "raylib.h"
#include "snake.h"
#include "game.h"
#include "menu.h"
#include "question.h"
#include <stddef.h>
#include <stdio.h>   

int score = 0;

char feedbackMessage[64] = "";
float feedbackTimer = 0.0f;
Color feedbackColor = WHITE;


typedef enum {
    THEME_LIGHT,
    THEME_DARK
} THEME;

THEME currentTheme = THEME_DARK;

Color bgColor = BLACK;
Color textColor = RAYWHITE;
Color buttonColor = DARKGREEN;
Color menuButtonColor = DARKBLUE; // Fixed color for the menu button

void updateColorsBasedOnTheme() {
    if (currentTheme == THEME_DARK) {
        bgColor = BLACK;
        textColor = RAYWHITE;
        buttonColor = DARKGREEN;
    } else {
        bgColor = RAYWHITE;
        textColor = BLACK;
        buttonColor = SKYBLUE;
    }
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60); 
    SetExitKey(KEY_NULL);

    GAME_STATE state = STATE_START_PAGE;

    SNAKE *snake = NULL;
    int food_x = 0;
    int food_y = 0;

    float moveTimer = 0.0f;
    float moveInterval = 0.15f; 

    bool showExitConfirmation = false; 

    updateColorsBasedOnTheme();
    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(bgColor);

        // ------------------ START PAGE ------------------
        if (state == STATE_START_PAGE)
        {
            DrawText("Snake Game", currentWidth / 2 - MeasureText("Snake Game", 40) / 2, 100, 40, textColor);

            Rectangle startBtn = {currentWidth / 2 - 150, 320, 300, 50};
            Rectangle menuBtn  = {currentWidth / 2 - 150, 390, 300, 50};
            Rectangle exitBtn  = {currentWidth / 2 - 150, 460, 300, 50};

            DrawRectangleRec(startBtn, buttonColor);
            DrawText("START", startBtn.x + startBtn.width / 2 - MeasureText("START", 20) / 2, startBtn.y + 15, 20, textColor);

            DrawRectangleRec(menuBtn, menuButtonColor); // Use fixed menu button color
            DrawText("MENU", menuBtn.x + menuBtn.width / 2 - MeasureText("MENU", 20) / 2, menuBtn.y + 15, 20, textColor);

            DrawRectangleRec(exitBtn, RED);
            DrawText("EXIT", exitBtn.x + exitBtn.width / 2 - MeasureText("EXIT", 20) / 2, exitBtn.y + 15, 20, RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startBtn))
                {
                    int midX = currentWidth / 2;
                    int midY = currentHeight / 2;

                    snake = create_snake((midX / 20), (midY / 20));
                    for (int i = 0; i < 20; i++) grow_snake(snake);

                    food_x = GetRandomValue(0, 39) * 20;
                    food_y = GetRandomValue(0, 22) * 20;
                    score = 0;
                    state = STATE_RUNNING;
                    moveTimer = 0.0f;
                }
                else if (CheckCollisionPointRec(mouse, menuBtn))
                {
                    state = STATE_MENU;
                }
                else if (CheckCollisionPointRec(mouse, exitBtn))
                {
                    showExitConfirmation = true; // Show confirmation tab
                }
            }

            // Exit confirmation tab
            if (showExitConfirmation)
            {
                Rectangle tab = {currentWidth / 2 - 150, currentHeight / 2 - 100, 340, 150};
                DrawRectangleRec(tab, GRAY);
                DrawText("Are you sure you want to exit?", tab.x + tab.width / 2 - MeasureText("Are you sure you want to exit?", 20) / 2, tab.y + 30, 20, BLACK);

                Rectangle yesBtn = {tab.x + tab.width / 2 - 110, tab.y + 100, 80, 40};
                Rectangle noBtn  = {tab.x + tab.width / 2 + 10,  tab.y + 100, 80, 40};

                DrawRectangleRec(yesBtn, DARKGREEN);
                DrawText("YES", yesBtn.x + yesBtn.width / 2 - MeasureText("YES", 20) / 2, yesBtn.y + 10, 20, RAYWHITE);

                DrawRectangleRec(noBtn, RED);
                DrawText("NO", noBtn.x + noBtn.width / 2 - MeasureText("NO", 20) / 2, noBtn.y + 10, 20, RAYWHITE);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mouse = GetMousePosition();
                    if (CheckCollisionPointRec(mouse, yesBtn))
                    {
                        CloseWindow(); // Exit the game
                        return 0;
                    }
                    else if (CheckCollisionPointRec(mouse, noBtn))
                    {
                        showExitConfirmation = false; // Hide confirmation tab
                    }
                }
            }
        }

        // ------------------ MENU ------------------
        else if (state == STATE_MENU)
        {
            draw_menu(&state);

            handle_menu_input(&state);         

            // Poziționarea butonului pentru schimbarea temei sub celelalte butoane
            Rectangle themeBtn = {currentWidth / 2 - 150, 460, 300, 50}; // Aceeași dimensiune ca celelalte butoane
            DrawRectangleRec(themeBtn, buttonColor);
            DrawText(currentTheme == THEME_DARK ? "Switch to Light Mode" : "Switch to Dark Mode", 
                themeBtn.x + themeBtn.width / 2 - MeasureText(currentTheme == THEME_DARK ? "Switch to Light Mode" : "Switch to Dark Mode", 20) / 2, 
                themeBtn.y + 15, 20, textColor);
            
            // Logica pentru schimbarea temei
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, themeBtn))
                {
                    currentTheme = (currentTheme == THEME_DARK) ? THEME_LIGHT : THEME_DARK;
                    updateColorsBasedOnTheme();
                }
            }
        }
        // ------------------ INSTRUCTIONS ------------------
        else if (state == STATE_INSTRUCTIONS)
        {
            draw_instructions(&state); 
        }
        // ------------------ GAME ------------------
        else if (state == STATE_RUNNING)
        {
            if (IsKeyPressed(KEY_P))
            {
                state = STATE_PAUSED;
            }

            Rectangle pausebutton = {SCREEN_WIDTH - 110, 10, 100, 40};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), pausebutton))
            {
                state = STATE_PAUSED;
            }

            if (IsKeyPressed(KEY_W) && snake->direction != DOWN) set_snake_direction(snake, UP);
            if (IsKeyPressed(KEY_S) && snake->direction != UP) set_snake_direction(snake, DOWN);
            if (IsKeyPressed(KEY_A) && snake->direction != RIGHT) set_snake_direction(snake, LEFT);
            if (IsKeyPressed(KEY_D) && snake->direction != LEFT) set_snake_direction(snake, RIGHT);

            moveTimer += GetFrameTime();
            if (moveTimer >= moveInterval)
            {
                move_snake(snake, food_x, food_y);
                update_game(snake, &score, &state, &food_x, &food_y);
                moveTimer = 0.0f;

                // Countdown the feedback message timer
            if (feedbackTimer > 0.0f) {
              feedbackTimer -= GetFrameTime();
            if (feedbackTimer <= 0.0f) {
             feedbackMessage[0] = '\0'; // Clear the message
    }
}
            }

            draw_pause_button();
            draw_snake(snake);

            if (feedbackTimer > 0.0f && feedbackMessage[0] != '\0') {
                int fontSize = 24;
                 int textWidth = MeasureText(feedbackMessage, fontSize);
                DrawText(feedbackMessage,
                 SCREEN_WIDTH / 2 - textWidth / 2,
                SCREEN_HEIGHT - 60,
                fontSize,
                feedbackColor);
}
        }
        // ------------------ PAUSED ------------------
        else if (state == STATE_PAUSED)
        {
            draw_pause_page();

            Rectangle triangleHitbox = {SCREEN_WIDTH - 40, 20, 20, 20}; 

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), triangleHitbox)) 
            {
                state = STATE_RUNNING;
                moveTimer = 0.0f;
            }

            Rectangle backBtn = {currentWidth / 2 - 75, currentHeight / 2 + 150, 160, 40};
            DrawRectangleRec(backBtn, GRAY);
            DrawText("Back to menu", backBtn.x + backBtn.width / 2 - MeasureText("Back to menu", 20) / 2, backBtn.y + 10, 20, BLACK);

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, backBtn))
                {
                    state = STATE_START_PAGE;
                    if (snake != NULL)
                    {
                        free_snake(snake);
                        snake = NULL;
                    }
                }
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
            {
                state = STATE_RUNNING;
                moveTimer = 0.0f;
            }
        }
        // ------------------ GAME OVER ------------------
        else if (state == STATE_GAME_OVER)
        {
            update_highscores(score);

            DrawText("Game Over", currentWidth / 2 - MeasureText("Game Over", 30) / 2, currentHeight / 2 - 30, 30, RED);
            DrawText("Press R to restart", currentWidth / 2 - MeasureText("Press R to restart", 20) / 2, currentHeight / 2 + 10, 20, WHITE);
            DrawText("Press ESC to return to menu", currentWidth / 2 - MeasureText("Press ESC to return to menu", 20) / 2, currentHeight / 2 + 40, 20, GRAY);

            if (IsKeyPressed(KEY_R))
            {
                reset_game(&snake, &score);
                for (int i = 0; i < 20; i++) grow_snake(snake);
                food_x = GetRandomValue(0, 39) * 20;
                food_y = GetRandomValue(0, 22) * 20;
                state = STATE_RUNNING;
                moveTimer = 0.0f;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = STATE_START_PAGE;
                if (snake != NULL)
                {
                    free_snake(snake);
                    snake = NULL;
                }
            }
        }

            // ------------------ HIGHSCORES ------------------
        if (state == STATE_HIGHSCORES) 
        {
            draw_highscores(&state);
        }

        EndDrawing();
    }

    if (snake != NULL)
        free_snake(snake);

    CloseWindow();
    return 0;
}