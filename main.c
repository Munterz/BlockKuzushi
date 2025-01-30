#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Block Kuzushi");
    SetTargetFPS(60);


    Rectangle paddle = { screenWidth / 2 - 50, screenHeight - 40, 100, 10 };
    int paddleSpeed = 8;

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_LEFT) && paddle.x > 0) {
            paddle.x -= paddleSpeed;
        }
        if (IsKeyDown(KEY_RIGHT) && paddle.x < screenWidth - paddle.width) {
            paddle.x += paddleSpeed;
        }

        BeginDrawing();
        ClearBackground(BLACK);


        DrawRectangleRec(paddle, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}