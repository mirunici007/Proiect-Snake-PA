#include "raylib.h"
#include "menu.h"
#include "game.h"
#include <stdio.h>

#define MAX_SCORES 3
#define HIGHSCORE_FILE "highscores.txt"

static int highscores[MAX_SCORES] = {0};
static int count = 0;

// Extern pentru culoarea textului (setată în main.c)
extern Color textColor;

void load_highscores()
{
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    count = 0;
    if (file == NULL)
    {
        return;
    }
    while (count < MAX_SCORES && fscanf(file, "%d", &highscores[count]) == 1)
    {
        count++;
    }
    fclose(file);
}

void save_highscores()
{
    FILE *file = fopen(HIGHSCORE_FILE, "w");
    if (file == NULL)
    {
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\n", highscores[i]);
    }
    fclose(file);
}

void update_highscores(int new_score)
{
    load_highscores();

    for (int i = 0; i < count; i++)
    {
        if (highscores[i] == new_score)
        {
            return; //score already exists
        }
    }
    for (int i = 0; i <= count; i++)
    {
        if (i == count || new_score > highscores[i])
        {
            if (count < MAX_SCORES)
            {
                count++;
            }
            for (int j = count - 1; j > i; j--)
            {
                highscores[j] = highscores[j - 1];
            }
            highscores[i] = new_score;
            break;
        }
    }
    save_highscores();
}

void draw_menu(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Snake Game - MENU", width / 2 - MeasureText("Snake Game - MENU", 40) / 2, height / 2 - 100, 40, GREEN);

    Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
    Rectangle highscores_button = {width / 2 - 150, 390, 300, 50};
    Rectangle settings_button = {width / 2 - 150, 530, 300, 50};
    Rectangle back_to_start_page = {width / 2 - 150, 600, 300, 50};

    DrawRectangleRec(instructions_button, DARKBLUE);
    DrawText("Instructions", instructions_button.x + instructions_button.width / 2 - MeasureText("Instructions", 20) / 2, instructions_button.y + 15, 20, GOLD);

    DrawRectangleRec(highscores_button, ORANGE);
    DrawText("Highscores", highscores_button.x + highscores_button.width / 2 - MeasureText("Highscores", 20) / 2, highscores_button.y + 15, 20, BLACK);

    DrawRectangleRec(settings_button, DARKGRAY);
    DrawText("Settings", settings_button.x + settings_button.width / 2 - MeasureText("Settings", 20) / 2, settings_button.y + 15, 20, GOLD);

    DrawRectangleRec(back_to_start_page, RED);
    DrawText("Back to Start Page", back_to_start_page.x + back_to_start_page.width / 2 - MeasureText("Back to Start Page", 20) / 2, back_to_start_page.y + 15, 20, GOLD);
}

void draw_instructions(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Instructions", width / 2 - MeasureText("Instructions", 40) / 2, height / 2 - 100, 40, textColor);
    DrawText("Use W,S,A,D to control the snake", width / 2 - MeasureText("Use W,S,A,D to control the snake", 20) / 2, height / 2 - 50, 20, textColor);
    DrawText("Eat the food and answer the questions correctly to grow the snake", width / 2 - MeasureText("Eat the food and answer the questions correctly to grow the snake", 20) / 2, height / 2, 20, textColor);
    DrawText("Avoid the walls and the snake's body", width / 2 - MeasureText("Avoid the walls and the snake's body", 20) / 2, height / 2 + 50, 20, textColor);

    Rectangle back_button = {width / 2 - 75, height / 2 + 100, 150, 40};
    DrawRectangleRec(back_button, DARKBLUE);
    DrawText("Back to Menu", back_button.x + back_button.width / 2 - MeasureText("Back to Menu", 20) / 2, back_button.y + 10, 20, GOLD);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), back_button))
    {
        *state = STATE_MENU;
    }
}

void draw_highscores(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("HIGHSCORES", width / 2 - MeasureText("HIGHSCORES", 40) / 2, height / 2 - 150, 40, textColor);

    load_highscores();

    if (count == 0)
    {
        DrawText("No scores available", width / 2 - MeasureText("No scores available", 20) / 2, height / 2 - 80, 20, textColor);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "%d. %d", i + 1, highscores[i]);
            DrawText(buffer, width / 2 - MeasureText(buffer, 30) / 2, height / 2 - 80 + i * 40, 30, textColor);
        }
    }

    Rectangle back_button = {width / 2 - 75, height / 2 + 100, 150, 40};
    DrawRectangleRec(back_button, DARKBLUE);
    DrawText("Back to Menu", back_button.x + back_button.width / 2 - MeasureText("Back to Menu", 20) / 2, back_button.y + 10, 20, GOLD);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), back_button))
    {
        *state = STATE_MENU;
    }
}

void handle_menu_input(GAME_STATE *state)
{
    int width = GetScreenWidth();
    Vector2 mouse = GetMousePosition();

    Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
    Rectangle highscores_button = {width / 2 - 150, 390, 300, 50};
    Rectangle settings_button = {width / 2 - 150, 530, 300, 50};
    Rectangle back_to_start_page = {width / 2 - 150, 600, 300, 50};

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, instructions_button))
        {
            *state = STATE_INSTRUCTIONS;
        }
        else if (CheckCollisionPointRec(mouse, highscores_button))
        {
            *state = STATE_HIGHSCORES;
        }
        else if(CheckCollisionPointRec(mouse, settings_button))
        {
            *state = STATE_SETTINGS;
        }
        else if (CheckCollisionPointRec(mouse, back_to_start_page))
        {
            *state = STATE_START_PAGE;
        }
    }
}

void draw_congrats_if_milestone(int score, int milestone, int screenWidth, int screenHeight) {
    if (score > milestone) {
        const char *message = "what a shame=((( but congrats! over 100 points for you.";
        int fontSize = 20;
        int textWidth = MeasureText(message, fontSize);
        int x = screenWidth / 2 - textWidth / 2;
        int y = screenHeight / 2 + 70;

        DrawText(message, x, y, fontSize, GOLD);
    }
}

void draw_settings(GAME_STATE *state, float *volume)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Settings", width / 2 - MeasureText("Settings", 40) / 2, height / 2 - 100, 40, textColor);

    // Bară volum
    Rectangle volumeBar = {width / 2 - 100, height / 2, 200, 20};
    float handleRadius = 12;
    float handleX = volumeBar.x + (*volume) * volumeBar.width;

    DrawRectangleRec(volumeBar, LIGHTGRAY);
    DrawRectangle(volumeBar.x, volumeBar.y, (*volume) * volumeBar.width, volumeBar.height, GREEN);
    DrawCircle((int)handleX, volumeBar.y + volumeBar.height / 2, handleRadius, DARKGREEN);

    // Drag volum
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, volumeBar)) {
        float percent = (mouse.x - volumeBar.x) / volumeBar.width;
        if (percent < 0.0f) percent = 0.0f;
        if (percent > 1.0f) percent = 1.0f;
        *volume = percent;
    }

    char volumeText[32];
    sprintf(volumeText, "Volume: %d%%", (int)(*volume * 100));
    DrawText(volumeText, width / 2 - MeasureText(volumeText, 20) / 2, height / 2 + 40, 20, textColor);

    // Buton back
    Rectangle back_button = {width / 2 - 75, height / 2 + 100, 150, 40};
    DrawRectangleRec(back_button, DARKGRAY);
    DrawText("Back to Menu", back_button.x + back_button.width / 2 - MeasureText("Back to Menu", 20) / 2, back_button.y + 10, 20, GOLD);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, back_button)) {
        *state = STATE_MENU;
    }
}