#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrix[20][20];
struct snake_head{
    int x;
    int y;
};

void spawn_food_1p(int* x,int*y){ //mancare care adauga 1p
    do {
        *x = rand() % 20;
        *y = rand() % 20;
    } while (matrix[*x][*y] != 0);
    matrix[*x][*y] = 2;
}

void spawn_food_2p(int* x,int*y){ //mancare care adauga 2p
    do {
        *x = rand() % 20;
        *y = rand() % 20;
    } while (matrix[*x][*y] != 0);
    matrix[*x][*y] = 3;
}

void spawn_food_minus1p(int* x,int*y){ //mancare care scade 1p
    do {
        *x = rand() % 20;
        *y = rand() % 20;
    } while (matrix[*x][*y] != 0);
    matrix[*x][*y] = 4;
}

int check_food(int* x, int* y, struct snake_head snake_head){
    if(matrix[snake_head.x][snake_head.y] == 2 || matrix[snake_head.x][snake_head.y] == 3|| matrix[snake_head.x][snake_head.y] == 4){
        matrix[snake_head.x][snake_head.y] = 0;
        return 1;
    }
    return 0;
}


//functia care imi alege aleatoriu ce tip de mancare sa adaug
void spawn_food_random_points(){
    int x, y;
    int random = rand() % 3 + 1;
    switch (random) {
        case 1:
            spawn_food_1p(&x, &y);
            break;
        case 2:
            spawn_food_2p(&x, &y);
            break;
        case 3:
            spawn_food_minus1p(&x, &y);
            break;
    }

}

void spawn_food(){
    while(check_self_collision() == 1){
        spawn_food_random_points();
    }//mai trebuie sa fac ca mancarea sa apara la un interval de timp dar nu am realizat inca cum 
}
//in main trebuie sa se apeleze srand(time(NULL)); inainte de a apela functia de spawn
//si functia draw_food care deseneaza mancarea o fac eu sau mai bine cui se ocupa de grafica?