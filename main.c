#include "snake.h"
#include "game.h"
#include "menu.h"
#include "food.h"
#include "question.h"
#include <stddef.h>
#include <stdio.h>   
#include <math.h>

int score = 0;
int foodsEaten = 0;  // Număr mâncăruri mâncate

Color LIGHTGREEN = (Color){152, 237, 66, 255};  
 



FOOD food;

char feedbackMessage[64] = "";
float feedbackTimer = 0.0f;
Color feedbackColor = WHITE;
Color scoreColor = RAYWHITE; // Default color for score

typedef enum {
    THEME_LIGHT,
    THEME_DARK
} THEME;

THEME currentTheme = THEME_DARK;

Color bgColor = BLACK;
Color textColor = RAYWHITE;
Color buttonColor = DARKGREEN;
Color menuButtonColor = DARKBLUE; // Fixed color for the menu button

void updateColorsBasedOnTheme() 

{
    if (currentTheme == THEME_DARK) {
        bgColor = BLACK;
        textColor = RAYWHITE;
        buttonColor = DARKGREEN;
        scoreColor = RAYWHITE; // White score for dark theme
    } else {
        bgColor = RAYWHITE;
        textColor = BLACK;
        buttonColor = SKYBLUE;
        scoreColor = BLACK; // Black score for light theme
    }
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60); 
    SetExitKey(KEY_NULL);

    GAME_STATE state = STATE_START_PAGE;

    SNAKE *snake = NULL;
    food.x = 0;
    food.y = 0;

    float moveTimer = 0.0f;
    float moveInterval = 0.15f; 

    bool showExitConfirmation = false; 
    bool foodJustEaten = false;  // Flag pentru a preveni dublarea mâncării
    bool showCredentials = false;

    updateColorsBasedOnTheme();
    load_highscores();
    initQuestions();
    Texture2D foodTexture = LoadTexture("textures/apple.png");
    Texture2D startBg = LoadTexture("textures/BACKGROUND.jpg");
    Texture2D grassBg = LoadTexture("textures/GRASS.jpg");
    
    InitAudioDevice();
    Music bgMusic = LoadMusicStream("textures/MUSIC.mp3");
    Sound rightSound = LoadSound("textures/RIGHT.wav");
    Sound wrongSound = LoadSound("textures/WRONG.wav");
    Sound gameOverSound = LoadSound("textures/GAME_OVER.wav");
    
    static bool playedGameOverSound = false;
    static bool muted = false;
    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(bgColor);

        // ------------------ START PAGE ------------------
        if (state == STATE_START_PAGE)
        {
            float scaleX = (float)currentWidth / startBg.width;
            float scaleY = (float)currentHeight / startBg.height;
            DrawTextureEx(startBg, (Vector2){0,0}, 0.0f, fmaxf(scaleX, scaleY), WHITE);
            
// Poziționare pentru colțul din dreapta sus
int cx = currentWidth - 80;
int cy = 80;

// Corp difuzor (dreptunghi GRI ÎNCHIS)
DrawRectangle(cx - 14, cy - 10, 12, 20, BLACK);

// Gura difuzorului (triunghi GRI ÎNCHIS)
Vector2 tri[3] = {
    {cx - 2, cy - 12},
    {cx + 14, cy},
    {cx - 2, cy + 12}
};
DrawTriangle(tri[0], tri[1], tri[2], BLACK);

// Unde sonore (arce groase GRI ÎNCHIS)
for (int i = 0; i < 2; i++) {
    int arcRadius = 12 + i * 6;
    int arcThickness = 3;
    for (int t = 0; t < arcThickness; t++) {
        DrawCircleLines(cx + 18, cy, arcRadius + t, BLACK);
    }
}

// Linie roșie groasă dacă e pe mute
if (muted) {
    DrawLineEx(
        (Vector2){cx - 16, cy - 16},
        (Vector2){cx + 28, cy + 16},
        5.0f, 
        RED
    );
}

// Detectează click pe o zonă dreptunghiulară din jurul iconiței
Rectangle volumeHitbox = {cx - 20, cy - 20, 48, 40};
if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, volumeHitbox)) {
        muted = !muted;
        SetMusicVolume(bgMusic, muted ? 0.0f : 1.0f);
    }
}

            // Eliminat titlul "Snake Game"
            // Mută butoanele mai jos
            int btnY = 260; // valoare mai mare pentru a le coborî
            Rectangle startBtn = {currentWidth / 2 - 150, btnY, 300, 50};
            Rectangle menuBtn  = {currentWidth / 2 - 150, btnY + 70, 300, 50};
            Rectangle credentialsBtn = {currentWidth / 2 - 150, btnY + 140, 300, 50};
            Rectangle exitBtn  = {currentWidth / 2 - 150, btnY + 210, 300, 50};

            DrawRectangleRec(startBtn, buttonColor);
            DrawText("START", startBtn.x + startBtn.width / 2 - MeasureText("START", 20) / 2, startBtn.y + 15, 20, textColor);

            DrawRectangleRec(menuBtn, menuButtonColor);
            DrawText("MENU", menuBtn.x + menuBtn.width / 2 - MeasureText("MENU", 20) / 2, menuBtn.y + 15, 20, textColor);

            DrawRectangleRec(credentialsBtn, GRAY);
            DrawText("CREDENTIALS", credentialsBtn.x + credentialsBtn.width / 2 - MeasureText("CREDENTIALS", 20) / 2, credentialsBtn.y + 15, 20, BLACK);

            DrawRectangleRec(exitBtn, RED);
            DrawText("EXIT", exitBtn.x + exitBtn.width / 2 - MeasureText("EXIT", 20) / 2, exitBtn.y + 15, 20, RAYWHITE);

            

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startBtn))
                {
                    int midX = currentWidth / 2;
                    int midY = currentHeight / 2;

                    snake = create_snake((midX / 20)* CELL_SIZE, (midY / 20)*CELL_SIZE);
                    

                    food.x = GetRandomValue(0, 39) * 20;
                    food.y = GetRandomValue(0, 22) * 20;
                    score = 0;
                    foodsEaten = 0;     // Resetare număr mâncăruri
                    state = STATE_RUNNING;
                    moveTimer = 0.0f;
                    foodJustEaten = false;  // Reset flag
                }
                else if (CheckCollisionPointRec(mouse, menuBtn))
                {
                    state = STATE_MENU;
                }
                else if (CheckCollisionPointRec(mouse, credentialsBtn))
                {
                    showCredentials = true;
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

            if (state == STATE_START_PAGE && showCredentials)
{
    // Overlay semitransparent
    DrawRectangle(0, 0, currentWidth, currentHeight, Fade(BLACK, 0.4f));

    // Caseta mărită
    Rectangle modal = {currentWidth / 2 - 275, currentHeight / 2 - 210, 550, 420};
    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 2, DARKGRAY);

    // Titlu (font mai mare)
    const char* title = "Credentials";
    int titleFontSize = 28;
    int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, modal.x + modal.width/2 - titleWidth/2, modal.y + 20, titleFontSize, DARKBLUE);

    // Textul (font mărit la 20px, spacing 6px)
    const char* credentialsText[] = {
        "Members:",
        "Sardaru Andreea-Miruna(314AC)",
        "Paraschiv Georgiana-Simona(314AC)",
        "Dumitrescu Laura(314AC)",
        "Flores-Botezatu Edyra-Alexia(314AC)",
        "Mitea Roberta-Elena(314AC)",
        "Stancu Patricia-Ioana(312AC)",
        "",
        "Coordinating teacher:",
        "Conf. Dr. Ing. Dan Mihail Caramihai"
    };
    int lines = sizeof(credentialsText)/sizeof(credentialsText[0]);
    int fontSize = 20;
    int spacing = 6;
    int startY = modal.y + 60;
    for (int i = 0; i < lines; i++) {
        int textWidth = MeasureText(credentialsText[i], fontSize);
        DrawText(credentialsText[i], modal.x + modal.width/2 - textWidth/2, startY + i*(fontSize+spacing), fontSize, BLACK);
    }

    // Buton BACK – rămâne centrat, puțin mai jos acum
    Rectangle backBtn = {modal.x + modal.width/2 - 60, modal.y + modal.height - 50, 120, 34};
    DrawRectangleRec(backBtn, LIGHTGRAY);
    DrawRectangleLinesEx(backBtn, 2, DARKGRAY);
    DrawText("BACK", backBtn.x + backBtn.width/2 - MeasureText("BACK", 18)/2, backBtn.y + 8, 18, BLACK);

    // Închidere la click pe BACK
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, backBtn)) {
            showCredentials = false;
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
            float scaleX = (float)currentWidth / grassBg.width;
            float scaleY = (float)currentHeight / grassBg.height;
            DrawTextureEx(grassBg, (Vector2){0,0}, 0.0f, fmaxf(scaleX, scaleY), WHITE);

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
                move_snake(snake, food.x, food.y);

                // Verificare și procesare coliziune mâncare cu flag corect
                if(check_food_collision(snake, food.x, food.y) && !foodJustEaten)
                {
                    // grow_snake(snake);
                    // score += 10;
                    // foodsEaten++;           // Incrementare număr mâncăruri mâncate
                    // food = spawn_food(snake);
                    state = STATE_QUESTION;         // <-- Treci în starea de întrebare!
                    selectRandomQuestion();
                    foodJustEaten = true;   // Blocăm dubla detectare până la următoarea mișcare

                }
                else if (!check_food_collision(snake, food.x, food.y))
                {
                    // Resetăm flagul doar când nu mai suntem pe mâncare, pentru a putea detecta următoarea coliziune
                    foodJustEaten = false;
                }

                update_game(snake, &score, &state, &food);
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
            draw_food(food, foodTexture);   

            // Afișează scorul și numărul de mâncăruri mâncate în colțul din stânga sus
            char scoreText[32];
            sprintf(scoreText, "Score: %d", score);
            DrawText(scoreText, 10, 10, 25, scoreColor); // Font size increased to 25

            char foodText[32];
            sprintf(foodText, "Foods eaten: %d", foodsEaten);
            DrawText(foodText, 10, 40, 20, ORANGE);

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
        else if (state == STATE_QUESTION)
        {
            if (currentQuestion != NULL) {
                // Desenează întrebarea și butoanele
                draw_question(currentQuestion);

                // Extrage răspunsurile pentru hitboxuri
                // int screenWidth = GetScreenWidth();
                // int y = 160, boxWidth = 800, boxHeight = 70, spacing = 30;
                // Rectangle answerBoxes[4];
                // for (int i = 0; i < 4; i++) {
                //     answerBoxes[i].x = screenWidth / 2 - boxWidth / 2;
                //     answerBoxes[i].y = y + i * (boxHeight + spacing);
                //     answerBoxes[i].width = boxWidth;
                //     answerBoxes[i].height = boxHeight;
                // }

                // // Mouse input
                // Vector2 mouse = GetMousePosition();
                // for (int i = 0; i < 4; i++) {
                //     if (CheckCollisionPointRec(mouse, answerBoxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                //         int result = ((i + 1) == currentQuestion->data.correctAnswer) ? 1 : 0;
                //         if (result == 1) {
                //             PlaySound(rightSound);
                //             // ... restul codului pentru răspuns corect ...
                //         } else {
                //             PlaySound(wrongSound);
                //             // ... restul codului pentru răspuns greșit ...
                //         }
                //         validate_answer(result, &score, snake, &food); // vezi mai jos funcția
                //         state = STATE_RUNNING;
                //         break;
                //     }
                // }

                        if (selectedAnswer != -1) {
            int result = (selectedAnswer == currentQuestion->data.correctAnswer) ? 1 : 0;
            if (result == 1) {
                PlaySound(rightSound);
                // ... restul codului pentru răspuns corect ...
            } else {
                PlaySound(wrongSound);
                // ... restul codului pentru răspuns greșit ...
            }
            validate_answer(result, &score, snake, &food);
            state = STATE_RUNNING;
            selectedAnswer = -1; // Reset pentru următoarea întrebare
        }

                // Tastatură: A/B/C/D sau 1/2/3/4
                // for (int i = 0; i < 4; i++) {
                //     if (IsKeyPressed(KEY_A + i) || IsKeyPressed(KEY_ONE + i) || IsKeyPressed(KEY_KP_1 + i)) {
                //         int result = ((i + 1) == currentQuestion->data.correctAnswer) ? 1 : 0;
                //         validate_answer(result, &score, snake, &food);
                //         state = STATE_RUNNING;
                //         break;
                //     }
                // }
            }
        }
        else if (state == STATE_HIGHSCORES)
        {
            draw_highscores(&state);
        }
        // ------------------ GAME OVER ------------------
        else if (state == STATE_GAME_OVER)
        {
            if (!playedGameOverSound) {
        PlaySound(gameOverSound);
        playedGameOverSound = true;
    }

            update_highscores(score);

            DrawText("Game Over", currentWidth / 2 - MeasureText("Game Over", 30) / 2, currentHeight / 2 - 30, 30, RED);

            // Actualizare culoare pentru textul "Press R to restart" și "Press ESC to return to menu"
            DrawText("Press R to restart", currentWidth / 2 - MeasureText("Press R to restart", 20) / 2, currentHeight / 2 + 10, 20, scoreColor);
            DrawText("Press ESC to return to menu", currentWidth / 2 - MeasureText("Press ESC to return to menu", 20) / 2, currentHeight / 2 + 40, 20, scoreColor);

            //afisare mesaj la depasire 100 de puncte
            draw_congrats_if_milestone(score, 100, currentWidth, currentHeight);

            if (IsKeyPressed(KEY_R))
            {
                reset_game(&snake, &score);
                foodsEaten = 0;  // Reset număr mâncăruri
                
                food.x = GetRandomValue(0, 39) * 20;
                food.y = GetRandomValue(0, 22) * 20;
                state = STATE_RUNNING;
                moveTimer = 0.0f;
                foodJustEaten = false;  // Reset flag
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
        else
        {
            playedGameOverSound = false;
        }

        if (state != STATE_RUNNING) {
    if (!IsMusicStreamPlaying(bgMusic)) {
        PlayMusicStream(bgMusic);
    }
} else {
    if (IsMusicStreamPlaying(bgMusic)) {
        PauseMusicStream(bgMusic);
    }
}
UpdateMusicStream(bgMusic); // Pune asta la fiecare frame!
SetMusicVolume(bgMusic, muted ? 0.0f : 1.0f);
SetSoundVolume(rightSound, muted ? 0.0f : 1.0f);
SetSoundVolume(wrongSound, muted ? 0.0f : 1.0f);
SetSoundVolume(gameOverSound, muted ? 0.0f : 1.0f);

        EndDrawing();
    }

    if (snake != NULL) free_snake(snake);
    UnloadTexture(startBg); // Unload the texture before closing
    UnloadTexture(grassBg);
    UnloadSound(rightSound);
UnloadSound(wrongSound);
UnloadSound(gameOverSound);
UnloadMusicStream(bgMusic);
CloseAudioDevice();
    CloseWindow();

    return 0;
}