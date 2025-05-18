#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include "snake.h"

// Dimensiunea unei celule din grid, în pixeli
#define CELL_SIZE 20

// Structura pentru mâncare
typedef struct Food {
    int x;
    int y;
} FOOD;

// Funcții pentru manipularea mâncării
FOOD spawn_food(SNAKE *snake);
void draw_food(FOOD food);
int food_on_snake(FOOD food,SNAKE *snake);

#endif // FOOD_H