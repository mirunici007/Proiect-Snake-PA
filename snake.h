#ifndef SNAKE_H
#define SNAKE_H

//directions for the snake
#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'

#include "raylib.h"

#define SEGMENT_SIZE 10 // Dimensiunea segmentelor șarpelui

//declaring the variables
typedef struct segment
{
    int coord_x;
    int coord_y;
    struct segment *next;
}SEGM;

typedef struct snake
{
    SEGM *head;
    SEGM *tail;
    int length;
    char direction; //directions: UP, DOWN, LEFT, RIGHT

    Texture2D head_texture; //texture for the head
    Texture2D body_texture; //texture for the body
}SNAKE;

//function prtotypes

// Creates a new snake segment with given coordinates
SEGM *create_segment(int x, int y);

// Creates a new snake
SNAKE *create_snake(int start_x, int start_y);

// Adds a new segment to the tail of the snake
void grow_snake(SNAKE *snake);

// Checks if the snake's head collides with the food
int check_food_collision(SNAKE *snake, int food_x, int food_y);

// Moves the snake in the current direction 
void move_snake(SNAKE *snake, int food_x, int food_y);

// Checks if the snake collides with itself
int check_self_collision(SNAKE *snake);

// Checks if the snake collides with the boundaries of the screen
int check_boundary_collision(SNAKE *snake, int width, int height);

// Sets the direction of the snake
void set_snake_direction(SNAKE *snake, char direction);

// Frees the memory allocated for the snake
void free_snake(SNAKE *snake);

void draw_snake(SNAKE *snake);


#endif //SNAKE_H