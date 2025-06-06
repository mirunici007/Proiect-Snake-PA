#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "game.h"
#include "menu.h"

// External variables
extern Color textColor;
extern Color buttonColor;
extern THEME currentTheme;
extern void updateColorsBasedOnTheme(void);

void draw_menu(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Snake Game - MENU", width / 2 - MeasureText("Snake Game - MENU", 40) / 2, height / 2 - 100, 40, GREEN);

    Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
    Rectangle settings_button = {width / 2 - 150, 390, 300, 50};
    Rectangle theme_button = {width / 2 - 150, 460, 300, 50};
    Rectangle back_to_start_page = {width / 2 - 150, 530, 300, 50};

    DrawRectangleRec(instructions_button, DARKBLUE);
    DrawText("Instructions", instructions_button.x + instructions_button.width / 2 - MeasureText("Instructions", 20) / 2, instructions_button.y + 15, 20, GOLD);

    DrawRectangleRec(settings_button, DARKGRAY);
    DrawText("Settings", settings_button.x + settings_button.width / 2 - MeasureText("Settings", 20) / 2, settings_button.y + 15, 20, GOLD);

    DrawRectangleRec(theme_button, buttonColor);
    const char* themeText = (currentTheme == THEME_DARK) ? "Switch to Light Mode" : "Switch to Dark Mode";
    DrawText(themeText, 
        theme_button.x + theme_button.width / 2 - MeasureText(themeText, 20) / 2, 
        theme_button.y + 15, 20, textColor);

    DrawRectangleRec(back_to_start_page, RED);
    DrawText("Back to Start Page", back_to_start_page.x + back_to_start_page.width / 2 - MeasureText("Back to Start Page", 20) / 2, back_to_start_page.y + 15, 20, GOLD);

    // Removed the theme button click handling from here - moved to handle_menu_input
}

void draw_instructions(GAME_STATE *state)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawText("Instructions", width / 2 - MeasureText("Instructions", 40) / 2, height / 2 - 100, 40, textColor);
    DrawText("Use W,S,A,D to control the snake", width / 2 - MeasureText("Use W,S,A,D to control the snake", 20) / 2, height / 2 - 50, 20, textColor);
    DrawText("Eat the food and answer the questions correctly to grow the snake", width / 2 - MeasureText("Eat the food and answer the questions correctly to grow the snake", 20) / 2, height / 2, 20, textColor);
    DrawText("Avoid the snake's body", width / 2 - MeasureText("Avoid the snake's body", 20) / 2, height / 2 + 50, 20, textColor);

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
    // Only process input if mouse button was just pressed (not held down)
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return;
    }

    int width = GetScreenWidth();
    Vector2 mouse = GetMousePosition();

    Rectangle instructions_button = {width / 2 - 150, 320, 300, 50};
    Rectangle settings_button = {width / 2 - 150, 390, 300, 50};
    Rectangle theme_button = {width / 2 - 150, 460, 300, 50};
    Rectangle back_to_start_page = {width / 2 - 150, 530, 300, 50};

    if (CheckCollisionPointRec(mouse, instructions_button))
    {
        *state = STATE_INSTRUCTIONS;
    }
    else if(CheckCollisionPointRec(mouse, settings_button))
    {
        *state = STATE_SETTINGS;
    }
    else if (CheckCollisionPointRec(mouse, theme_button))
    {
        printf("Theme button clicked! Current theme: %d\n", currentTheme); // Debug print
        
        // Toggle theme - more explicit approach
        if (currentTheme == THEME_DARK)
        {
            currentTheme = THEME_LIGHT;
            printf("Switched to THEME_LIGHT (value: %d)\n", currentTheme); // Debug print
        }
        else
        {
            currentTheme = THEME_DARK;
            printf("Switched to THEME_DARK (value: %d)\n", currentTheme); // Debug print
        }
        
        updateColorsBasedOnTheme();
        printf("After updateColorsBasedOnTheme, theme is: %d\n", currentTheme); // Debug print
    }
    else if (CheckCollisionPointRec(mouse, back_to_start_page))
    {
        *state = STATE_START_PAGE;
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