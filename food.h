#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

typedef enum {
    FOOD_1P = 2,
    FOOD_2P = 3,
} FOOD_TYPE;

typedef struct food_node {
    int x, y;
    FOOD_TYPE type;
    struct food_node* next;
} FOOD;

FOOD* food_list = NULL;

void spawn_food_1p(SEGM* snake, int* x, int* y);
void spawn_food_2p(SEGM* snake, int* x, int* y);
void spawn_food_minus1p(SEGM* snake, int* x, int* y);
int is_position_occupied(SEGM* snake, int x, int y);
int check_food(int x, int y, int* grow_value);
void spawn_food_random_points(SEGM* snake);
void spawn_food(SEGM* snake);
void draw_food();   

#endif