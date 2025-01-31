#include "raylib.h"

#define ROWS 5
#define COLUMNS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 20

typedef struct {
    Rectangle rect;
    bool active;
    Color color;
    bool isPowerUp;
} Block;

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
    int score = 0;
    bool gameOver = false;
    bool gameWon = false;

    Color rowColors[ROWS] = { RED, ORANGE, YELLOW, GREEN, BLUE };

    Block blocks[ROWS * COLUMNS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            blocks[i * COLUMNS + j].rect = (Rectangle){ j * (BLOCK_WIDTH + 5) + 25, i * (BLOCK_HEIGHT + 5) + 50, BLOCK_WIDTH, BLOCK_HEIGHT };
            blocks[i * COLUMNS + j].active = true;
            blocks[i * COLUMNS + j].color = rowColors[i];
            blocks[i * COLUMNS + j].isPowerUp = false;
        }
    }

    int powerUp1 = GetRandomValue(0, ROWS * COLUMNS - 1);
    int powerUp2;
    do {
        powerUp2 = GetRandomValue(0, ROWS * COLUMNS - 1);
    } while (powerUp2 == powerUp1);

    blocks[powerUp1].isPowerUp = true;
    blocks[powerUp1].color = PURPLE;
    blocks[powerUp2].isPowerUp = true;
    blocks[powerUp2].color = PURPLE;

    while (!WindowShouldClose()) {
        if (!gameOver && !gameWon) {
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

            int blocksRemaining = 0;
            for (int i = 0; i < ROWS * COLUMNS; i++) {
                if (blocks[i].active) {
                    blocksRemaining++;
                }
            }

            for (int i = 0; i < ROWS * COLUMNS; i++) {
                if (blocks[i].active && CheckCollisionCircleRec(ballPosition, ballRadius, blocks[i].rect)) {
                    blocks[i].active = false;
                    ballSpeed.y *= -1;
                    score += 10;

                    if (blocks[i].isPowerUp) {
                        lives++;
                    }
                    break;
                }
            }

            if (blocksRemaining == 0) {
                gameWon = true;
            }

            if (blocksRemaining < (ROWS * COLUMNS) / 2) {
                ballSpeed.x = (ballSpeed.x > 0) ? 5 : -5;
                ballSpeed.y = (ballSpeed.y > 0) ? 5 : -5;
            }

            if (blocksRemaining < (ROWS * COLUMNS) / 4) {
                ballSpeed.x = (ballSpeed.x > 0) ? 6 : -6;
                ballSpeed.y = (ballSpeed.y > 0) ? 6 : -6;
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
                score = 0;
                gameOver = false;
                gameWon = false;
                ballPosition = (Vector2){ screenWidth / 2, screenHeight / 2 };
                ballSpeed = (Vector2){ 4, -4 };
                paddle.x = screenWidth / 2 - paddle.width / 2;

                for (int i = 0; i < ROWS * COLUMNS; i++) {
                    blocks[i].active = true;
                    blocks[i].isPowerUp = false;
                    blocks[i].color = rowColors[i / COLUMNS];
                }

                int powerUp1 = GetRandomValue(0, ROWS * COLUMNS - 1);
                int powerUp2;
                do {
                    powerUp2 = GetRandomValue(0, ROWS * COLUMNS - 1);
                } while (powerUp2 == powerUp1);

                blocks[powerUp1].isPowerUp = true;
                blocks[powerUp1].color = PURPLE;
                blocks[powerUp2].isPowerUp = true;
                blocks[powerUp2].color = PURPLE;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (gameOver) {
            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press ENTER to restart", screenWidth / 2 - 140, screenHeight / 2 + 30, 20, WHITE);
        } else if (gameWon) {
            DrawText("YOU WIN!", screenWidth / 2 - 80, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press ENTER to restart", screenWidth / 2 - 140, screenHeight / 2 + 30, 20, WHITE);
        } else {
            DrawRectangleRec(paddle, WHITE);
            DrawCircleV(ballPosition, ballRadius, WHITE);
            DrawText(TextFormat("Lives: %d", lives), 10, 10, 20, WHITE);
            DrawText(TextFormat("Score: %d", score), screenWidth - 120, 10, 20, WHITE);

            for (int i = 0; i < ROWS * COLUMNS; i++) {
                if (blocks[i].active) {
                    DrawRectangleRec(blocks[i].rect, blocks[i].color);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
