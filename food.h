#ifndef FOOD_H
#define FOOD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "snake.h"

#define CELL_SIZE 20  // dimensiunea unui pătrat din grid, în pixeli



typedef enum {
    FOOD_1P = 2,
    FOOD_2P = 3,
} FOOD_TYPE;

typedef struct food_node {
    int x, y;
    FOOD_TYPE type;
    struct food_node* next; 
} FOOD;
extern FOOD* food_list;

void spawn_food_1p(SNAKE *snake, int *x, int *y);
void spawn_food_2p(SNAKE *snake, int *x, int *y);
int is_position_occupied(SNAKE *snake, int x, int y);
int check_food(SNAKE *snake, int x, int y, int *grow_value);
void spawn_food_random_points(SNAKE *snake);
void spawn_food(SNAKE *snake);
void draw_food();
void clear_food();

#endif