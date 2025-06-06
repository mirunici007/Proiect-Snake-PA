#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "question.h"
#include "snake.h"
#include "food.h" // adăugat

#define CELL_SIZE 20

extern Color feedbackColor;
extern char feedbackMessage[64];
extern float feedbackTimer;
extern FOOD food;
Texture2D foodTexture;  

//void apply_question_result(SNAKE *snake, int *score, int result);

// Init
void init_game(SNAKE **snake, int *score)
{
    *snake = create_snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    *score = 0;
    srand(time(NULL));

    
    food = spawn_food(*snake);
}

// Update
void update_game(SNAKE *snake, int *score, GAME_STATE *state, FOOD *food)
{
    Rectangle pausebutton = {SCREEN_WIDTH - 110, 10, 100, 40};
    // Rectangle lightModeBtn = {SCREEN_WIDTH - 110, 60, 100, 40}; // elimină dacă nu mai folosești

    if (IsKeyPressed(KEY_P) || 
       (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), pausebutton)))
    {
        *state = (*state == STATE_RUNNING) ? STATE_PAUSED : STATE_RUNNING;
    }

    // ȘTERGE acest bloc:
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), lightModeBtn)) {
    //     isLightMode = !isLightMode; // schimbă modul
    // }

    if (*state == STATE_RUNNING)
    {
        move_snake(snake, (*food).x, (*food).y);

        if (check_food_collision(snake, (*food).x, (*food).y))
        {
            *state = STATE_QUESTION;
            selectRandomQuestion();
        }

        if (check_collisions(snake))
        {
            *state = STATE_GAME_OVER;
            printf("Game over! Final score: %d\n", *score);
            return;
        }
    }
}

// Reset
void reset_game(SNAKE **snake, int *score)
{
    free_snake(*snake);
    *snake = create_snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    *score = 0;

    food = spawn_food(*snake);
}

// Coliziuni
int check_collisions(SNAKE *snake)
{
    if (check_self_collision(snake)) return 1;
    return 0;
}

// UI: pauză
void draw_pause_page()
{
    DrawRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 120, LIGHTGRAY); 
    DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 60) / 2, SCREEN_HEIGHT / 2 - 20, 60, BLACK);        
    DrawText("Press P to Resume", SCREEN_WIDTH / 2 - MeasureText("Press P to Resume", 20) / 2, SCREEN_HEIGHT / 2 + 35, 20, DARKGRAY); 

    int margin = 20;
    int size = 20;
    Vector2 v1 = {SCREEN_WIDTH - margin - size, margin};
    Vector2 v2 = {SCREEN_WIDTH - margin, margin + size / 2};
    Vector2 v3 = {SCREEN_WIDTH - margin - size, margin + size};

    DrawTriangle(v1, v2, v3, RED);
    DrawLineV(v1, v2, RED);
    DrawLineV(v2, v3, RED);
    DrawLineV(v3, v1, RED);
}

void draw_pause_button()
{
    int bar_width = 10;
    int bar_height = 20;
    int bar_spacing = 5;
    int bar_x = SCREEN_WIDTH - 90;
    int bar_y = 20;

    DrawRectangle(bar_x, bar_y, bar_width, bar_height, DARKGREEN);
    DrawRectangle(bar_x + bar_width + bar_spacing, bar_y, bar_width, bar_height, DARKGREEN);
}

// input pentru întrebări
int get_answer_index() {
    int answerIndex;
    printf("Enter answer index (0-3): ");
    if (scanf("%d", &answerIndex) != 1 || answerIndex < 0 || answerIndex > 3) {
        while (getchar() != '\n'); // curăță buffer
        return -1;
    }
    return answerIndex;
}

// răspuns la întrebare
void handle_input(SNAKE *snake, GAME_STATE *state, int *score) {
    int answerIndex = get_answer_index();

    int result;
    if (answerIndex == -1) {
        result = -1;
    } else {
        //int userAnswer = currentQuestion->data.correctAnswer;
        result = checkAnswer(answerIndex + 1) ? 1 : 0;
    }

    //apply_question_result(snake, score, result);
    validate_answer(result, score, snake, &food); 

    //food = spawn_food(snake);

    *state = STATE_RUNNING;
}

void validate_answer(int result, int* score, SNAKE* snake, FOOD* food) {
    if (result == 1) {
        *score += 10;
        grow_snake(snake);
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Right answer! +10 points.");
        feedbackColor = GREEN;
    } else {
        *score -= 5;
        if (*score < 0) *score = 0;
        shrink_snake(snake);
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Wrong answer! -5 points.");
        feedbackColor = RED;
    }
    *food = spawn_food(snake);
    feedbackTimer = 2.0f;
}

// aplică rezultat întrebare
// void apply_question_result(SNAKE *snake, int *score, int result)
// {
//     switch (result) {
//         case 1:
//             *score += 10;
//             grow_snake(snake);
//             snprintf(feedbackMessage, sizeof(feedbackMessage), "Raspuns corect! +10 puncte.");
//             feedbackColor = GREEN;
//             break;
//         case 0:
//             *score -= 5;
//             snprintf(feedbackMessage, sizeof(feedbackMessage), "Raspuns gresit! -5 puncte.");
//             feedbackColor = RED;
//             break;
//         case -1:
//             *score -= 5;
//             snprintf(feedbackMessage, sizeof(feedbackMessage), "Raspuns invalid. -5 puncte.");
//             feedbackColor = ORANGE;
//             break;
//     }

//     if (*score < 0) *score = 0;
//     feedbackTimer = 2.0f;
// }

void draw_game(SNAKE *snake, FOOD *food, int score, GAME_STATE state) {
    BeginDrawing();

    ClearBackground(bgColor); // folosește culoarea globală

    if (state == STATE_RUNNING) {
        draw_snake(snake);
        draw_food(*food, foodTexture);
        draw_pause_button();
    } else if (state == STATE_PAUSED) {
        draw_pause_page();
    } else if (state == STATE_QUESTION) {
        draw_question(currentQuestion);
    }

    EndDrawing();
}