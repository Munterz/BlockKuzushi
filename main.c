#include "raylib.h"

int main() {
    InitWindow(800, 600, "Block Kuzushi");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib test", 300, 280, 20, DARKGRAY);
        EndDrawing();
    }
//test
    CloseWindow();
    return 0;
}