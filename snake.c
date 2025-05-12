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

    // Load the head texture based on the initial direction
    snake->head_up_texture = LoadTexture("textures/head_up.png");
    snake->head_down_texture = LoadTexture("textures/head_down.png");
    snake->head_left_texture = LoadTexture("textures/head_left.png");
    snake->head_right_texture = LoadTexture("textures/head_right.png");
    // Load the body texture
    snake->body_horizontal_texture = LoadTexture("textures/body_orizontal.png");
    snake->body_vertical_texture = LoadTexture("textures/body_vertical.png");

    // Load corner textures
    snake->corner_bottom_right_texture = LoadTexture("textures/corner_top_left.png");
    snake->corner_bottom_left_texture = LoadTexture("textures/corner_top_right.png");
    snake->corner_top_right_texture = LoadTexture("textures/corner_bottom_left.png");
    snake->corner_top_left_texture = LoadTexture("textures/corner_bottom_right.png");

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
    return (snake->head->coord_x == food_x && 
            snake->head->coord_y == food_y);
}

void move_snake(SNAKE *snake, int food_x, int food_y) {
    int prev_x = snake->head->coord_x;
    int prev_y = snake->head->coord_y;

    // Ajustează poziția capului în funcție de direcție
    switch (snake->direction) {
        case 'W': prev_y -= 2; break; // sus (deplasare cu 2 unități)
        case 'S': prev_y += 2; break; // jos (deplasare cu 2 unități)
        case 'A': prev_x -= 2; break; // stânga (deplasare cu 2 unități)
        case 'D': prev_x += 2; break; // dreapta (deplasare cu 2 unități)
        default: break;
    }

    // Creează un nou cap
    SEGM *new_head = create_segment(prev_x, prev_y);
    new_head->next = snake->head;
    snake->head = new_head;

    // Verifică dacă șarpele mănâncă mâncarea
    if (check_food_collision(snake, food_x, food_y)) {
        snake->length++;
    } else {
        // Elimină segmentul cozii
        SEGM *temp = snake->head;
        while (temp->next && temp->next != snake->tail) {
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

    UnloadTexture(snake->head_up_texture);
    UnloadTexture(snake->head_down_texture);
    UnloadTexture(snake->head_left_texture);
    UnloadTexture(snake->head_right_texture);

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

    // Alege textura capului în funcție de direcție
    Texture2D head_texture;
    switch (snake->direction) {
        case 'W': head_texture = snake->head_up_texture; break;    // sus
        case 'S': head_texture = snake->head_down_texture; break;  // jos
        case 'A': head_texture = snake->head_left_texture; break;  // stânga
        case 'D': head_texture = snake->head_right_texture; break; // dreapta
        default: head_texture = snake->head_right_texture; break;  // fallback
    }

    // Desenează capul șarpelui
    DrawTexture(
        head_texture,
        current->coord_x * SEGMENT_SIZE,
        current->coord_y * SEGMENT_SIZE,
        WHITE
    );

    // Treci la următorul segment
    SEGM *prev = current;
    current = current->next;

    // Desenează corpul șarpelui
    while (current != NULL) {
        // Alege textura corpului în funcție de direcție
        Texture2D body_texture;
        if (current->coord_x != prev->coord_x) {
            body_texture = snake->body_horizontal_texture; // orizontal (stânga/dreapta)
        } else {
            body_texture = snake->body_vertical_texture;   // vertical (sus/jos)
        }

        // Verifică dacă este un colț
        if (current->next != NULL) {
            SEGM *next = current->next;

            if ((prev->coord_x < current->coord_x && next->coord_y < current->coord_y) || // dreapta sus
                (prev->coord_y < current->coord_y && next->coord_x < current->coord_x)) { // sus stânga
                DrawTexture(
                    snake->corner_top_left_texture,
                    current->coord_x * SEGMENT_SIZE,
                    current->coord_y * SEGMENT_SIZE,
                    WHITE
                );
            } else if ((prev->coord_x > current->coord_x && next->coord_y < current->coord_y) || // stânga sus
                       (prev->coord_y < current->coord_y && next->coord_x > current->coord_x)) { // sus dreapta
                DrawTexture(
                    snake->corner_top_right_texture,
                    current->coord_x * SEGMENT_SIZE,
                    current->coord_y * SEGMENT_SIZE,
                    WHITE
                );
            } else if ((prev->coord_x < current->coord_x && next->coord_y > current->coord_y) || // dreapta jos
                       (prev->coord_y > current->coord_y && next->coord_x < current->coord_x)) { // jos stânga
                DrawTexture(
                    snake->corner_bottom_left_texture,
                    current->coord_x * SEGMENT_SIZE,
                    current->coord_y * SEGMENT_SIZE,
                    WHITE
                );
            } else if ((prev->coord_x > current->coord_x && next->coord_y > current->coord_y) || // stânga jos
                       (prev->coord_y > current->coord_y && next->coord_x > current->coord_x)) { // jos dreapta
                DrawTexture(
                    snake->corner_bottom_right_texture,
                    current->coord_x * SEGMENT_SIZE,
                    current->coord_y * SEGMENT_SIZE,
                    WHITE
                );
            }
        }

        // Desenează segmentul corpului
        DrawTexture(
            body_texture,
            current->coord_x * SEGMENT_SIZE,
            current->coord_y * SEGMENT_SIZE,
            WHITE
        );

        // Actualizează segmentul anterior
        prev = current;
        current = current->next;
    }
}