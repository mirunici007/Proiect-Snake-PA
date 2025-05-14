
#include "food.h"

int is_position_occupied(SEGM* snake, int x, int y) {
    while (snake) {
        if (snake->coord_x == x && snake->coord_y == y)
            return 1;
        snake = snake->next;
    }
    for (FOOD* f = food_list; f != NULL; f = f->next) {
        if (f->x == x && f->y == y)
            return 1;
    }
    return 0;
}

void spawn_food_1p(SEGM* snake, int* x, int* y) {
    do {
        *x = rand() % 20;
        *y = rand() % 20;
    } while (is_position_occupied(snake, *x, *y));

    FOOD* f = malloc(sizeof(FOOD));
    f->x = *x;
    f->y = *y;
    f->type = FOOD_1P;
    f->next = food_list;
    food_list = f;
}

void spawn_food_2p(SEGM* snake, int* x, int* y) {
    do {
        *x = rand() % 20;
        *y = rand() % 20;
    } while (is_position_occupied(snake, *x, *y));

    FOOD* f = malloc(sizeof(FOOD));
    f->x = *x;
    f->y = *y;
    f->type = FOOD_2P;
    f->next = food_list;
    food_list = f;
}


int check_food(int x, int y, int* grow_value) {
    FOOD* prev = NULL;
    FOOD* curr = food_list;

    while (curr) {
        if (curr->x == x && curr->y == y) {
            *grow_value = (curr->type == FOOD_1P) ? 1 :
                          (curr->type == FOOD_2P) ? 2 : -1;

            if (prev)
                prev->next = curr->next;
            else
                food_list = curr->next;

            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }

    return 0;
}

void spawn_food_random_points(SEGM* snake) {
    int x, y;
    int random = rand() % 2 + 1;
    switch (random) {
        case 1:
            spawn_food_1p(snake, &x, &y);
            break;
        case 2:
            spawn_food_2p(snake, &x, &y);
            break;

    }
}


void spawn_food(SEGM* snake) {
    static time_t last_spawn_time = 0;
    time_t current_time = time(NULL);

    // Dacă au trecut 2 secunde
    if (difftime(current_time, last_spawn_time) >= 2.0) {
        spawn_food_random_points(snake);
        last_spawn_time = current_time;
    }
}


#define CELL_SIZE 20  // dimensiunea unui pătrat din grid, în pixeli

void draw_food() {
    FOOD* curr = food_list;
    while (curr) {
        int px = curr->x * CELL_SIZE;
        int py = curr->y * CELL_SIZE;

        switch (curr->type) {
            case FOOD_1P:
                DrawCircle(px + CELL_SIZE / 2, py + CELL_SIZE / 2, 6, GREEN); // măr mic verde
                break;
            case FOOD_2P:
                DrawCircle(px + CELL_SIZE / 2, py + CELL_SIZE / 2, 10, RED);  // măr mare roșu
                break;
        }

        curr = curr->next;
    }
}

