#include "snake.h"
#include "game.h"
#include "menu.h"
#include "food.h"
#include "question.h"
#include <stdio.h>
#include <math.h>

//global variables
int score = 0;
float volume = 1.0f;
FOOD food;
char feedbackMessage[64] = "";
float feedbackTimer = 0.0f;
Color feedbackColor;
Color scoreColor;
THEME currentTheme = THEME_DARK;
Color bgColor;
Color textColor;
Color buttonColor;
Color menuButtonColor;

static void initializeColors(void)
{
    if (currentTheme == THEME_DARK)
    {
        bgColor = BLACK;
        textColor = GOLD;
        buttonColor = DARKGREEN;
        scoreColor = GOLD;
        feedbackColor = WHITE;
        menuButtonColor = DARKBLUE;
    }
    else
    {
        bgColor = RAYWHITE;
        textColor = DARKBLUE;
        buttonColor = SKYBLUE;
        scoreColor = BLACK;
        feedbackColor = BLACK;
        menuButtonColor = LIGHTGRAY;
    }
}

void updateColorsBasedOnTheme(void)
{
    //currentTheme == THEME_DARK ? "dark" : "light";
    initializeColors();
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    //initialize colors once at startup
    initializeColors();

    GAME_STATE state = STATE_START_PAGE;
    SNAKE *snake = NULL;
    food.x = 0;
    food.y = 0;

    float moveTimer = 0.0f;
    float moveInterval = 0.20f;

    bool showExitConfirmation = false;
    bool foodJustEaten = false;
    bool showCredentials = false;

    //initialize questions, audio, load textures, and music
    initQuestions();
    Texture2D foodTexture = LoadTexture("textures/apple.png");
    Texture2D startBg = LoadTexture("textures/BACKGROUND.jpg");
    Texture2D grassBg = LoadTexture("textures/GRASS.jpg");

    InitAudioDevice();
    Music bgMusic = LoadMusicStream("textures/MUSIC.mp3");
    Music runningMusic = LoadMusicStream("textures/RUNNING_MUSIC.mp3");
    Music questionMusic = LoadMusicStream("textures/QUESTION.mp3");
    Sound rightSound = LoadSound("textures/RIGHT.wav");
    Sound wrongSound = LoadSound("textures/WRONG.mp3");
    Sound gameOverSound = LoadSound("textures/GAME_OVER.wav");

    if (foodTexture.id == 0 || startBg.id == 0 || grassBg.id == 0)
    {
        fprintf(stderr, "Failed to load one or more textures.\n");
        CloseWindow();
        return 1;
    }

    if (!IsAudioDeviceReady())
    {
        fprintf(stderr, "Audio device failed to initialize.\n");
        UnloadTexture(foodTexture);
        UnloadTexture(startBg);
        UnloadTexture(grassBg);
        CloseWindow();
        return 1;
    }
    if (bgMusic.stream.buffer == NULL || runningMusic.stream.buffer == NULL || questionMusic.stream.buffer == NULL)
    {
        fprintf(stderr, "Failed to load one or more music streams.\n");
        UnloadTexture(foodTexture);
        UnloadTexture(startBg);
        UnloadTexture(grassBg);
        CloseAudioDevice();
        CloseWindow();
        return 1;
    }
    static bool muted = false;
    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(bgColor);

        //START PAGE
        if (state == STATE_START_PAGE)
        {
            float scaleX = (float)currentWidth / startBg.width;
            float scaleY = (float)currentHeight / startBg.height;
            DrawTextureEx(startBg, (Vector2)
            {
                0,0
            }, 0.0f, fmaxf(scaleX, scaleY), WHITE);

            //positioning the volume icon and label
            int cx = currentWidth - 80;
            int cy = 80;

            //draw the volume icon(speaker)
            DrawRectangle(cx - 14, cy - 10, 12, 20, BLACK);
            Vector2 tri[3] =
            {
                {cx - 2, cy - 12},
                {cx + 14, cy},
                {cx - 2, cy + 12}
            };
            DrawTriangle(tri[0], tri[1], tri[2], BLACK);

            //draw the sound waves
            for (int i = 0; i < 2; i++)
            {
                int arcRadius = 12 + i * 6;
                int arcThickness = 3;
                for (int t = 0; t < arcThickness; t++)
                {
                    DrawCircleLines(cx + 18, cy, arcRadius + t, BLACK);
                }
            }

            //draw a red line across the speaker if muted
            if (muted)
            {
                DrawLineEx((Vector2)
                {
                    cx - 16, cy - 16
                },(Vector2)
                {
                    cx + 28, cy + 16
                },5.0f,RED);
            }
            Rectangle volumeHitbox = {cx - 20, cy - 20, 48, 40};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, volumeHitbox))
                {
                    muted = !muted;
                }
            }

            //text label for the volume icon
            int musicLabelFontSize = 16;
            const char* musicLabel = "Music";
            int musicLabelWidth = MeasureText(musicLabel, musicLabelFontSize);
            DrawText(musicLabel, cx - musicLabelWidth/2 + 7, cy + 22, musicLabelFontSize, BLACK);

            //positions for the buttons
            int btnY = 260;
            Rectangle startBtn = {currentWidth / 2 - 150, btnY, 300, 50};
            Rectangle menuBtn  = {currentWidth / 2 - 150, btnY + 70, 300, 50};
            Rectangle credentialsBtn = {currentWidth / 2 - 150, btnY + 140, 300, 50};
            Rectangle exitBtn  = {currentWidth / 2 - 150, btnY + 210, 300, 50};

            DrawRectangleRec(startBtn, buttonColor);
            DrawText("START", startBtn.x + startBtn.width / 2 - MeasureText("START", 20) / 2, startBtn.y + 15, 20, textColor);

            DrawRectangleRec(menuBtn, menuButtonColor);
            DrawText("MENU", menuBtn.x + menuBtn.width / 2 - MeasureText("MENU", 20) / 2, menuBtn.y + 15, 20, textColor);

            DrawRectangleRec(credentialsBtn, YELLOW);
            DrawText("CREDENTIALS", credentialsBtn.x + credentialsBtn.width / 2 - MeasureText("CREDENTIALS", 20) / 2, credentialsBtn.y + 15, 20, BLACK);

            DrawRectangleRec(exitBtn, RED);
            DrawText("EXIT", exitBtn.x + exitBtn.width / 2 - MeasureText("EXIT", 20) / 2, exitBtn.y + 15, 20, GOLD);



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
                    state = STATE_RUNNING;
                    moveTimer = 0.0f;
                    foodJustEaten = false;
                    //reset feedback message and timer
                    feedbackMessage[0] = '\0';
                    feedbackTimer = 0.0f;
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
                    //show confirmation tab
                    showExitConfirmation = true;
                }
            }


            //exit confirmation tab
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
                        //exit the game
                        CloseWindow();
                    }
                    else if (CheckCollisionPointRec(mouse, noBtn))
                    {
                        //hide confirmation tab
                        showExitConfirmation = false;
                    }
                }
            }

            if (state == STATE_START_PAGE && showCredentials)
            {
                //overlay semitransparent for the credentials modal
                DrawRectangle(0, 0, currentWidth, currentHeight, Fade(BLACK, 0.4f));

                Rectangle modal = {currentWidth / 2 - 275, currentHeight / 2 - 210, 550, 420};
                DrawRectangleRec(modal, RAYWHITE);
                DrawRectangleLinesEx(modal, 2, DARKGRAY);

                //title for the modal
                const char* title = "Credentials";
                int titleFontSize = 28;
                int titleWidth = MeasureText(title, titleFontSize);
                DrawText(title, modal.x + modal.width/2 - titleWidth/2, modal.y + 20, titleFontSize, DARKBLUE);

                //list of credentials
                const char* credentialsText[] =
                {
                    "Members:",
                    "Sardaru Andreea-Miruna(314AC)",
                    "Paraschiv Georgiana-Simona(314AC)",
                    "Dumitrescu Laura(314AC)",
                    "Flores-Botezatu Edyra-Alexia(314AC)",
                    "Mitea Roberta-Elena(314AC)",
                    "",
                    "Coordinating teacher:",
                    "Conf. Dr. Ing. Dan Mihail Caramihai"
                };
                int lines = sizeof(credentialsText)/sizeof(credentialsText[0]);
                int fontSize = 20;
                int spacing = 6;
                int startY = modal.y + 60;
                for (int i = 0; i < lines; i++)
                {
                    int textWidth = MeasureText(credentialsText[i], fontSize);
                    DrawText(credentialsText[i], modal.x + modal.width/2 - textWidth/2, startY + i*(fontSize+spacing), fontSize, BLACK);
                }

                //draw the BACK button at the bottom of the modal
                Rectangle backBtn = {modal.x + modal.width/2 - 60, modal.y + modal.height - 50, 120, 34};
                DrawRectangleRec(backBtn, LIGHTGRAY);
                DrawRectangleLinesEx(backBtn, 2, DARKGRAY);
                DrawText("BACK", backBtn.x + backBtn.width/2 - MeasureText("BACK", 18)/2, backBtn.y + 8, 18, GOLD);

                //handle the BACK button click
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mouse = GetMousePosition();
                    if (CheckCollisionPointRec(mouse, backBtn))
                    {
                        showCredentials = false;
                    }
                }
            }

        }

        //MENU PAGE
        else if (state == STATE_MENU)
        {
            draw_menu(&state);

            handle_menu_input(&state);

        }
        //INSTRUCTIONS PAGE
        else if (state == STATE_INSTRUCTIONS)
        {
            draw_instructions(&state);
        }
        //GAME RUNNING PAGE
        else if (state == STATE_RUNNING)
        {
            if (snake == NULL)
            {
                state = STATE_START_PAGE;
                continue;
            }

            float scaleX = (float)currentWidth / grassBg.width;
            float scaleY = (float)currentHeight / grassBg.height;
            DrawTextureEx(grassBg, (Vector2)
            {
                0,0
            }, 0.0f, fmaxf(scaleX, scaleY), WHITE);

            if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
            {
                state = STATE_PAUSED;
            }

            Rectangle pausebutton = {SCREEN_WIDTH - 110, 10, 100, 40};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), pausebutton))
            {
                state = STATE_PAUSED;
            }

            //set directions for the snake based on key presses, but prevent reversing direction
            if (IsKeyPressed(KEY_W) && snake->direction != DOWN) set_snake_direction(snake, UP);
            if (IsKeyPressed(KEY_S) && snake->direction != UP) set_snake_direction(snake, DOWN);
            if (IsKeyPressed(KEY_A) && snake->direction != RIGHT) set_snake_direction(snake, LEFT);
            if (IsKeyPressed(KEY_D) && snake->direction != LEFT) set_snake_direction(snake, RIGHT);


            //delete the feedback message if any of the movement keys are pressed
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
            {
                feedbackMessage[0] = '\0';
                feedbackTimer = 0.0f;
            }

            moveTimer += GetFrameTime();
            if (moveTimer >= moveInterval)
            {
                move_snake(snake, food.x, food.y);

                //verify food collision and if the food was just eaten, then show a question
                if(check_food_collision(snake, food.x, food.y) && !foodJustEaten)
                {
                    state = STATE_QUESTION;
                    selectRandomQuestion();
                    foodJustEaten = true;
                }
                else if (!check_food_collision(snake, food.x, food.y))
                {
                    foodJustEaten = false;
                }

                update_game(snake, &score, &state, &food);
                moveTimer = 0.0f;

                //countdown the feedback message timer
                if (feedbackTimer > 0.0f)
                {
                    feedbackTimer -= GetFrameTime();
                    if (feedbackTimer <= 0.0f)
                    {
                        feedbackMessage[0] = '\0'; //clear the message
                    }
                }
            }

            draw_pause_button();
            draw_snake(snake);
            draw_food(food, foodTexture);

            //display the score at the top left corner of the screen
            char scoreText[32];
            sprintf(scoreText, "Score: %d", score);
            DrawText(scoreText, 10, 10, 25, scoreColor);


            if (feedbackTimer > 0.0f && feedbackMessage[0] != '\0')
            {
                int fontSize = 24;
                int textWidth = MeasureText(feedbackMessage, fontSize);
                DrawText(feedbackMessage,
                         SCREEN_WIDTH / 2 - textWidth / 2,
                         SCREEN_HEIGHT - 60,
                         fontSize,
                         feedbackColor);
            }
        }
        //PAUSE PAGE
        else if (state == STATE_PAUSED)
        {
            draw_pause_page();

            Rectangle triangleHitbox = {SCREEN_WIDTH - 40, 20, 20, 20};

            //if the user clicks the triangle button, resume the game
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), triangleHitbox))
            {
                state = STATE_RUNNING;
                moveTimer = 0.0f;
            }

            Rectangle backBtn = {currentWidth / 2 - 75, currentHeight / 2 + 150, 160, 40};
            DrawRectangleRec(backBtn, GRAY);
            DrawText("Back to menu", backBtn.x + backBtn.width / 2 - MeasureText("Back to menu", 20) / 2, backBtn.y + 10, 20, GOLD);

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

            //allow the user to resume the game by pressing ENTER, ESCAPE, or P
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
            {
                state = STATE_RUNNING;
                moveTimer = 0.0f;
            }
        }
        else if (state == STATE_QUESTION)
        {
            if (currentQuestion != NULL)
            {
                draw_question(currentQuestion);

                if (selectedAnswer != -1)
                {
                    int result = (selectedAnswer == currentQuestion->data.correctAnswer) ? 1 : 0;
                    if (result == 1)
                    {
                        PlaySound(rightSound);
                    }
                    else
                    {
                        PlaySound(wrongSound);
                    }
                    validate_answer(result, &score, snake, &food);
                    state = STATE_RUNNING;
                    //reset the selected answer for the next question
                    selectedAnswer = -1;
                }
            }
        }
        else if (state == STATE_SETTINGS)
        {
            draw_settings(&state, &volume);
            SetMusicVolume(bgMusic, muted ? 0.0f : volume);
            SetMusicVolume(runningMusic, muted ? 0.0f : volume);
            SetMusicVolume(questionMusic, muted ? 0.0f : volume);
            SetSoundVolume(rightSound, muted ? 0.0f : volume);
            SetSoundVolume(wrongSound, muted ? 0.0f : volume);
            SetSoundVolume(gameOverSound, muted ? 0.0f : volume);
        }
        else if (state == STATE_GAME_OVER)
        {
            int gameOverFontSize = 54;
            int finalScoreFontSize = 36;

            DrawText("Game Over", currentWidth / 2 - MeasureText("Game Over", gameOverFontSize) / 2, currentHeight / 2 - 90, gameOverFontSize, RED);

            //display the final score in the center of the screen
            char finalScoreText[32];
            sprintf(finalScoreText, "Final score: %d", score);
            DrawText(finalScoreText, currentWidth / 2 - MeasureText(finalScoreText, finalScoreFontSize) / 2, currentHeight / 2 - 20, finalScoreFontSize, GREEN);

            DrawText("Press R to restart", currentWidth / 2 - MeasureText("Press R to restart", 20) / 2, currentHeight / 2 + 40, 20, scoreColor);
            DrawText("Press ESC to return to menu", currentWidth / 2 - MeasureText("Press ESC to return to menu", 20) / 2, currentHeight / 2 + 70, 20, scoreColor);

            draw_congrats_if_milestone(score, 100, currentWidth, currentHeight);

            if (IsKeyPressed(KEY_R))
            {
                reset_game(&snake, &score);
                food.x = GetRandomValue(0, 39) * 20;
                food.y = GetRandomValue(0, 22) * 20;
                state = STATE_RUNNING;
                moveTimer = 0.0f;
                foodJustEaten = false;
                //delete the feedback message and reset the timer
                feedbackMessage[0] = '\0';
                feedbackTimer = 0.0f;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = STATE_START_PAGE;
                if (snake != NULL)
                {
                    free_snake(snake);
                    snake = NULL;
                }
                //delete the feedback message when returning to the menu
                feedbackMessage[0] = '\0';
                feedbackTimer = 0.0f;
            }
        }

        //control the music based on the current state
        if (state == STATE_QUESTION)
        {
            //stop bgMusic and runningMusic if they are playing
            if (IsMusicStreamPlaying(bgMusic)) PauseMusicStream(bgMusic);
            if (IsMusicStreamPlaying(runningMusic)) PauseMusicStream(runningMusic);

            //start playing questionMusic if it's not already playing
            if (!IsMusicStreamPlaying(questionMusic))
            {
                PlayMusicStream(questionMusic);
            }
        }
        else
        {
            //stop questionMusic if it's playing
            if (IsMusicStreamPlaying(questionMusic)) PauseMusicStream(questionMusic);

            //control bgMusic and runningMusic based on the current state
            if (state != STATE_RUNNING)
            {
                if (!IsMusicStreamPlaying(bgMusic))
                {
                    PlayMusicStream(bgMusic);
                }
                if (IsMusicStreamPlaying(runningMusic))
                {
                    PauseMusicStream(runningMusic);
                }
            }
            else
            {
                if (!IsMusicStreamPlaying(runningMusic))
                {
                    PlayMusicStream(runningMusic);
                }
                if (IsMusicStreamPlaying(bgMusic))
                {
                    PauseMusicStream(bgMusic);
                }
            }
        }

        UpdateMusicStream(bgMusic);
        UpdateMusicStream(runningMusic);
        UpdateMusicStream(questionMusic);

        //set the volume for all music and sound effects based on the muted state and volume level
        SetMusicVolume(bgMusic, muted ? 0.0f : volume);
        SetMusicVolume(runningMusic, muted ? 0.0f : volume);
        SetMusicVolume(questionMusic, muted ? 0.0f : volume);
        SetSoundVolume(rightSound, muted ? 0.0f : volume);
        SetSoundVolume(wrongSound, muted ? 0.0f : volume);
        SetSoundVolume(gameOverSound, muted ? 0.0f : volume);

        EndDrawing();
    }

    if (snake != NULL) free_snake(snake);
    //unload textures before closing
    UnloadTexture(startBg);
    UnloadTexture(grassBg);
    UnloadSound(rightSound);
    UnloadSound(wrongSound);
    UnloadSound(gameOverSound);
    UnloadMusicStream(bgMusic);
    UnloadMusicStream(runningMusic);
    UnloadMusicStream(questionMusic);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
