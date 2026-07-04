 #ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include "snake.h"

//the size of a cell in pixels
#define CELL_SIZE 20

//the struct for the food
typedef struct Food {
    int x;
    int y;
} FOOD;

//functions for food management
FOOD spawn_food(SNAKE *snake);
void draw_food(FOOD food, Texture2D food_texture);
int food_on_snake(FOOD food,SNAKE *snake);

#endif