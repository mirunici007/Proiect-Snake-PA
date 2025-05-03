#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake.h"

//declaring the functions

//function for creating a new snake segment
SEGM *create_segment(int x, int y)
{
    SEGM *new_segment = (SEGM *)malloc(sizeof(SEGM));

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
    snake->direction = 'R'; // initial direction to the right

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

void move_snake(SNAKE *snake)
{
    int new_x = snake->head->coord_x;
    int new_y = snake->head->coord_y;

    //adjust the new position based on the direction
    switch(snake->direction)
    {
        case 'W': new_y += 1; break; //up
        case 'S': new_y -= 1; break; //down
        case 'A': new_x -= 1; break; //left
        case 'D': new_x += 1; break; //right
        default: break;
    }

    // create a new head
    SEGM *new_head = create_segment(new_x, new_y);
    new_head->next = snake->head;
    snake->head = new_head;

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