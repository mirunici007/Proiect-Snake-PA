#ifndef SNAKE_H
#define SNAKE_H

//directions for the snake
#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'

#include "raylib.h"

#define SEGMENT_SIZE 20 // Dimensiunea segmentelor șarpelui

//declaring the variables

typedef struct {
    const char* head_up;
    const char* head_down;
    const char* head_left;
    const char* head_right;
    const char* body_horizontal;
    const char* body_vertical;
    const char* corner_top_left;
    const char* corner_top_right;
    const char* corner_bottom_left;
    const char* corner_bottom_right;
    const char* tail_up;
    const char* tail_down;
    const char* tail_left;
    const char* tail_right;
} SnakeTexturePaths;


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

    Texture2D head_up_texture;    // Textura pentru cap (sus)
    Texture2D head_down_texture;  // Textura pentru cap (jos)
    Texture2D head_left_texture;  // Textura pentru cap (stânga)
    Texture2D head_right_texture; // Textura pentru cap (dreapta)
    Texture2D body_texture; //texture for the body

    Texture2D body_horizontal_texture; // Textura pentru corp (orizontal: stânga/dreapta)
    Texture2D body_vertical_texture;   // Textura pentru corp (vertical: sus/jos)

    // Texturi pentru colțuri
    Texture2D corner_top_left_texture;     // colț stânga sus
    Texture2D corner_top_right_texture;    // colț dreapta sus
    Texture2D corner_bottom_left_texture;  // colț stânga jos
    Texture2D corner_bottom_right_texture; // colț dreapta jos

    Texture2D tail_up_texture;    // Textura pentru coada (sus)
    Texture2D tail_down_texture;  // Textura pentru coada (jos)
    Texture2D tail_left_texture;  // Textura pentru coada (stânga)
    Texture2D tail_right_texture; // Textura pentru coada (dreapta)
}SNAKE;

//function prtotypes

// Creates a new snake segment with given coordinates
SEGM *create_segment(int x, int y);

// Creates a new snake
SNAKE *create_snake(int start_x, int start_y);

// Adds a new segment to the tail of the snake
void grow_snake(SNAKE *snake);

void shrink_snake(SNAKE *snake);

// Checks if the snake's head collides with the food
int check_food_collision(SNAKE *snake, int food_x, int food_y);

// Moves the snake in the current direction 
void move_snake(SNAKE *snake, int food_x, int food_y);

// Checks if the snake collides with itself
int check_self_collision(SNAKE *snake);

// Checks if the snake collides with the boundaries of the screen
int check_boundary_collision(SNAKE *snake, int width, int height);

//Checks if the snake collides with the walls or itself
int check_collisions(SNAKE *snake);

//Sets the direction of the snake
void set_snake_direction(SNAKE *snake, char direction);

// Frees the memory allocated for the snake
void free_snake(SNAKE *snake);

void draw_snake(SNAKE *snake);

#endif //SNAKE_H