#include "food.h"
#include <stdlib.h>
#include "game.h"
#include <math.h>

#define FOOD_HISTORY_SIZE 5
#define MIN_FOOD_DISTANCE 4 * CELL_SIZE // distanța minimă între mâncăruri

static FOOD food_history[FOOD_HISTORY_SIZE];
static int food_history_count = 0;

// Verifică dacă mâncarea e pe șarpe
int food_on_snake(FOOD food, SNAKE *snake) {
    SEGM *current = snake->head;
    while (current != NULL) {
        if (current->coord_x == food.x && current->coord_y == food.y) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Verifică dacă mâncarea e prea aproape de o mâncare anterioară
int food_too_close_to_previous(FOOD food) {
    for (int i = 0; i < food_history_count; i++) {
        float dx = (float)(food.x - food_history[i].x);
        float dy = (float)(food.y - food_history[i].y);
        float distance = sqrtf(dx * dx + dy * dy);

        if (distance < MIN_FOOD_DISTANCE) {
            return 1; // Prea aproape
        }
    }
    return 0; // Distanță acceptabilă
}

// Generează mâncare într-un loc sigur
FOOD spawn_food(SNAKE *snake) {
    FOOD food;
    int max_x = (SCREEN_WIDTH / CELL_SIZE) - 2;
    int max_y = (SCREEN_HEIGHT / CELL_SIZE) - 2;

    do {
        food.x = (1 + rand() % max_x) * CELL_SIZE;
        food.y = (1 + rand() % max_y) * CELL_SIZE;
    } while (food_on_snake(food, snake) || food_too_close_to_previous(food));

    // Salvăm în istoric
    if (food_history_count < FOOD_HISTORY_SIZE) {
        food_history[food_history_count++] = food;
    } else {
        for (int i = 1; i < FOOD_HISTORY_SIZE; i++) {
            food_history[i - 1] = food_history[i];
        }
        food_history[FOOD_HISTORY_SIZE - 1] = food;
    }

    return food;
}

// Desenează mâncarea
void draw_food(FOOD food) {
    DrawCircle(food.x + CELL_SIZE / 2, food.y + CELL_SIZE / 2, CELL_SIZE / 2, RED);
}
