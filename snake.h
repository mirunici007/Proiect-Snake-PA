#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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
    char direction; 
}SNAKE;

//declaring the functions




#endif //SNAKE_H