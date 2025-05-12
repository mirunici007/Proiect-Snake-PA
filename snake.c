#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake.h"

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

void shrink_snake(SNAKE *snake)
{
    if (snake->length <= 1)
    {
        printf("Snake is already at minimum length\n");
        return;
    }
    SEGM *current = snake->head;

    while (current->next != snake->tail)
    {
        current = current->next;
    }
    free(snake->tail);
    current->next = NULL;
    snake->tail = current;
    snake->length--;
}

//function to check if the sbake's head collides with the food
//1 for collision
int check_food_collision(SNAKE *snake, int food_x, int food_y)
{
    return (snake->head->coord_x == food_x && snake->head->coord_y == food_y);
}

void move_snake(SNAKE *snake, int food_x, int food_y)
{
    int new_x = snake->head->coord_x;
    int new_y = snake->head->coord_y;

    //adjust the new position based on the direction
    switch(snake->direction)
    {
        case 'W': new_y -= 1; break; //up
        case 'S': new_y += 1; break; //down
        case 'A': new_x -= 1; break; //left
        case 'D': new_x += 1; break; //right
        default: break;
    }

    // create a new head
    SEGM *new_head = create_segment(new_x, new_y);
    new_head->next = snake->head;
    snake->head = new_head;

    //checkif the snake eats food
    if(check_food_collision(snake, food_x, food_y))
    {
        snake->length++;
    }
    else
    {
        //remove the tail segment
        SEGM *temp = snake->head;
        while(temp->next && temp->next != snake->tail)
        {
            temp = temp->next;
        }

        free(snake->tail);
        temp->next = NULL;
        snake->tail = temp;
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