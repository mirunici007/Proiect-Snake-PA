
#include "game.h"
#include "food.h"


// Verifică dacă poziția este ocupată de șarpe sau mâncare
int is_position_occupied(SNAKE *snake, int x, int y) {
    SEGM *segment = snake->head;
    while (segment) {
        if (segment->coord_x == x && segment->coord_y == y)
            return 1;
        segment = segment->next;
    }
    for (FOOD *f = food_list; f != NULL; f = f->next) {
        if (f->x == x && f->y == y)
            return 1;
    }
    return 0;
}

void spawn_food_1p(SNAKE *snake, int *x, int *y) {
    do {
        *x = rand() % (SCREEN_WIDTH / CELL_SIZE);  // Coordonate aleatorii în grilă
        *y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
    } while (is_position_occupied(snake, *x, *y));

    FOOD *f = malloc(sizeof(FOOD));
    f->x = *x;
    f->y = *y;
    f->type = FOOD_1P;
    f->next = food_list;
    food_list = f;
}

void spawn_food_2p(SNAKE *snake, int *x, int *y) {
    do {
        *x = rand() % (SCREEN_WIDTH / CELL_SIZE);  // Coordonate aleatorii în grilă
        *y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
    } while (is_position_occupied(snake, *x, *y));

    FOOD *f = malloc(sizeof(FOOD));
    f->x = *x;
    f->y = *y;
    f->type = FOOD_2P;
    f->next = food_list;
    food_list = f;
}

int check_food(SNAKE *snake, int x, int y, int *grow_value) {
    FOOD *prev = NULL;
    FOOD *curr = food_list;

    while (curr) {
        if (curr->x == x && curr->y == y) {
            *grow_value = (curr->type == FOOD_1P) ? 1 : 2;


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

void spawn_food_random_points(SNAKE *snake) {
    int x, y;
    int random = rand() % 2 + 1;
    if (random == 1) {
        spawn_food_1p(snake, &x, &y);
    } else {
        spawn_food_2p(snake, &x, &y);
    }
}


void spawn_food(SNAKE *snake) {
    static time_t last_spawn_time = 0;
    time_t current_time = time(NULL);

    // Dacă au trecut 2 secunde
    if (difftime(current_time, last_spawn_time) >= 2.0) {
        spawn_food_random_points(snake);
        last_spawn_time = current_time;
    }
}


// Desenează mâncarea pe ecran
void draw_food() {
    FOOD *curr = food_list;
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

