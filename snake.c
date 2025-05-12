#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake.h"
#include "raylib.h"

#define SEGMENT_SIZE 20 // Dimensiunea segmentelor șarpelui

//declaring the functions

//function for creating a new snake segment
SEGM *create_segment(int x, int y)
{
    SEGM *new_segment = (SEGM *)malloc(sizeof(SEGM));
    if(new_segment == NULL)
    {
        printf("Memory allocation failed for segment\n");
        exit(1);
    }
    
    new_segment->coord_x = x;
    new_segment->coord_y = y;
    new_segment->next = NULL;

    return new_segment;
}

//function for creating a new snake
SNAKE *create_snake(int start_x, int start_y)
{
    SNAKE *snake = (SNAKE *)malloc(sizeof(SNAKE));
    if(snake == NULL)
    {
        printf("Memory allocation failed for snake\n");
        exit(1);
    }

    snake->head = create_segment(start_x, start_y);
    snake->tail = snake->head;
    snake->length = 1;
    snake->direction = 'D'; // initial direction is right
    snake->head_texture = LoadTexture("textures/head.png");
    snake->body_texture = LoadTexture("textures/body.png"); 



    return snake;
}

//function for growing the snake
void grow_snake(SNAKE *snake)
{
    SEGM *new_segment = create_segment(snake->tail->coord_x, snake->tail->coord_y);

    snake->tail->next = new_segment;
    snake->tail = new_segment;
    snake->length++;
}

//function to check if the sbake's head collides with the food
//1 for collision
int check_food_collision(SNAKE *snake, int food_x, int food_y)
{
    return (snake->head->coord_x == food_x && snake->head->coord_y == food_y);
}

void move_snake(SNAKE *snake, int food_x, int food_y) {
    // Salvează poziția anterioară a capului
    int prev_x = snake->head->coord_x;
    int prev_y = snake->head->coord_y;

    // Actualizează poziția capului în funcție de direcție
    switch (snake->direction) {
        case 'W': snake->head->coord_y -= 1; break; // sus
        case 'S': snake->head->coord_y += 1; break; // jos
        case 'A': snake->head->coord_x -= 1; break; // stânga
        case 'D': snake->head->coord_x += 1; break; // dreapta
        default: break;
    }

    // Mută corpul șarpelui
    SEGM *current = snake->head->next;
    while (current != NULL) {
        int temp_x = current->coord_x;
        int temp_y = current->coord_y;

        current->coord_x = prev_x;
        current->coord_y = prev_y;

        prev_x = temp_x;
        prev_y = temp_y;

        current = current->next;
    }

}

int check_self_collision(SNAKE *snake)
{
    SEGM *current = snake->head->next;

    while(current)
    {
        if(snake->head->coord_x == current->coord_x && 
            snake->head->coord_y == current->coord_y)
        {
            return 1; //collision detected
        }

        current = current->next;
    }

    return 0; // no collision
}

//function for collision with the boundaries
int check_boundary_collision(SNAKE *snake, int screen_width, int screen_height)
{
    return (snake->head->coord_x < 0 || snake->head->coord_x >= screen_width ||
            snake->head->coord_y < 0 || snake->head->coord_y >= screen_height); 
}

//function for freeing the snake
void free_snake(SNAKE *snake)
{
    SEGM *current = snake->head;

    while(current)
    {
        SEGM *temp = current;
        current = current->next;
        free(temp);
    }
    UnloadTexture(snake->head_texture); // Unload the texture
    UnloadTexture(snake->body_texture);
    free(snake);
}

void set_snake_direction(SNAKE *snake, char direction)
{
    if ((direction == 'W' && snake->direction != 'S') || 
        (direction == 'S' && snake->direction != 'W') || 
        (direction == 'A' && snake->direction != 'D') || 
        (direction == 'D' && snake->direction != 'A'))
    {
        snake->direction = direction;
    }
}

void draw_snake(SNAKE *snake) {
    SEGM *current = snake->head;

    DrawTexture(snake->head_texture, current->coord_x*SEGMENT_SIZE, current->coord_y*SEGMENT_SIZE, WHITE);
    current = current->next;


    while (current != NULL) {
        // Desenează fiecare segment al șarpelui ca un dreptunghi verde
        DrawTexture(snake->body_texture, current->coord_x * SEGMENT_SIZE, current->coord_y * SEGMENT_SIZE, WHITE);
        
        current = current->next; // Treci la următorul segment
    }
}