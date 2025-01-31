#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Block Kuzushi");
    SetTargetFPS(60);

    Rectangle paddle = { screenWidth / 2 - 50, screenHeight - 40, 100, 10 };
    int paddleSpeed = 5;

    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 ballSpeed = { 4, -4 };
    float ballRadius = 8;

    int lives = 3;
    bool gameOver = false;

    while (!WindowShouldClose()) {
        if (!gameOver) {
            if (IsKeyDown(KEY_LEFT) && paddle.x > 0) {
                paddle.x -= paddleSpeed;
            }
            if (IsKeyDown(KEY_RIGHT) && paddle.x < screenWidth - paddle.width) {
                paddle.x += paddleSpeed;
            }

            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            if (ballPosition.x - ballRadius <= 0 || ballPosition.x + ballRadius >= screenWidth) {
                ballSpeed.x *= -1;
            }

            if (ballPosition.y - ballRadius <= 0) {
                ballSpeed.y *= -1;
            }

            if (CheckCollisionCircleRec(ballPosition, ballRadius, paddle) && ballSpeed.y > 0) {
                ballSpeed.y *= -1;
                ballPosition.y = paddle.y - ballRadius;
            }

            if (ballPosition.y > screenHeight) {
                lives--;
                if (lives <= 0) {
                    gameOver = true;
                } else {
                    ballPosition = (Vector2){ screenWidth / 2, screenHeight / 2 };
                    ballSpeed = (Vector2){ 4, -4 };
                }
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                lives = 3;
                gameOver = false;
                ballPosition = (Vector2){ screenWidth / 2, screenHeight / 2 };
                ballSpeed = (Vector2){ 4, -4 };
                paddle.x = screenWidth / 2 - paddle.width / 2;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (gameOver) {
            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press ENTER to restart", screenWidth / 2 - 140, screenHeight / 2 + 30, 20, WHITE);
        } else {
            DrawRectangleRec(paddle, WHITE);
            DrawCircleV(ballPosition, ballRadius, WHITE);
            DrawText(TextFormat("Lives: %d", lives), 10, 10, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
