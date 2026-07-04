#ifndef SNAKE_H
#define SNAKE_H

//directions for the snake
#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'

#include "raylib.h"

//segment size for the snake
#define SEGMENT_SIZE 20

//declaring the variables(the parts for the textures of the snake)
typedef struct
{
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
} SEGM;

typedef struct snake
{
    SEGM *head;
    SEGM *tail;
    int length;
    //directions: UP, DOWN, LEFT, RIGHT
    char direction;

    //textures for the snake's head for each direction(up,down,left,right)
    Texture2D head_up_texture;
    Texture2D head_down_texture;
    Texture2D head_left_texture;
    Texture2D head_right_texture;
    //texture for the body
    Texture2D body_texture;
    //textures for the snake's body for each horizontal direction(left,right)
    Texture2D body_horizontal_texture;
    //texture for the snake's body for each vertical direction(up,down)
    Texture2D body_vertical_texture;

    //textures for the snake's corners
    Texture2D corner_top_left_texture;
    Texture2D corner_top_right_texture;
    Texture2D corner_bottom_left_texture;
    Texture2D corner_bottom_right_texture;

    //textures for the snake's tail for each direction(up,down,left,right)
    Texture2D tail_up_texture;
    Texture2D tail_down_texture;
    Texture2D tail_left_texture;
    Texture2D tail_right_texture;
} SNAKE;

//function prtotypes

//creates a new segment with given coordinates
SEGM *create_segment(int x, int y);

//creates a new snake
SNAKE *create_snake(int start_x, int start_y);

//adds a new segment to the tail of the snake
void grow_snake(SNAKE *snake);

//removes the last segment of the snake
void shrink_snake(SNAKE *snake);

//checks if the snake's head collides with the food
int check_food_collision(SNAKE *snake, int food_x, int food_y);

//moves the snake in the current direction
void move_snake(SNAKE *snake, int food_x, int food_y);

//checks if the snake collides with itself
int check_self_collision(SNAKE *snake);

//checks if the snake collides with the boundaries of the screen
int check_boundary_collision(SNAKE *snake, int width, int height);

//checks if the snake collides with the walls or itself
int check_collisions(SNAKE *snake);

//sets the direction of the snake
void set_snake_direction(SNAKE *snake, char direction);

//frees the memory allocated for the snake
void free_snake(SNAKE *snake);


void draw_snake(SNAKE *snake);

#endif
