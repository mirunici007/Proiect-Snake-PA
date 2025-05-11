#include "raylib.h"

int main(void) {
    // Inițializează fereastra
    InitWindow(800, 450, "Test Raylib");

    // Setează FPS-ul țintă
    SetTargetFPS(60);

    // Bucla principală
    while (!WindowShouldClose()) {
        // Începe desenarea
        BeginDrawing();

        // Setează fundalul
        ClearBackground(RAYWHITE);

        // Afișează text
        DrawText("Raylib este configurat corect!", 190, 200, 20, DARKGRAY);

        // Termină desenarea
        EndDrawing();
    }

    // Închide fereastra
    CloseWindow();

    return 0;
}