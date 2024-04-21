#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/strutils.h"
#include "headers/movement.h"
#include "headers/collision.h"
#include "headers/window.h"

#define MAX_STRING_SIZE 256

typedef struct {
    int width; int height;
    char title[MAX_STRING_SIZE];
    size_t titleSize;
} Window;

void createWindow(Window *window, const char *title, int width, int height);

int main() {
    Window gameWindow;
    const char TITLE[] = "Ping-Pong game";

    createWindow(&gameWindow, TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(TARGET_FPS);
    InitWindow(gameWindow.width, gameWindow.height, gameWindow.title);

    float playerY = SCREEN_HEIGHT / 2 - 25;
    const float speed = getDeltaSpeed();

    const int entityWidth = 10;
    const int entityHeight = 50;
    const Color entityColor = WHITE;
    Entity player = {entityWidth, entityHeight, entityColor};
    CPU cpu = {{entityWidth, entityHeight, entityColor}, {SCREEN_WIDTH - entityWidth, SCREEN_HEIGHT / 2 - 25}};

    Ball ball = {10, entityColor, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {speed, speed}};

    const int textSize = 20;
    const int countX = SCREEN_WIDTH / 2 - textSize;
    char* countText = NULL;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) playerY -= speed;
        if (IsKeyDown(KEY_S)) playerY += speed;

        if (playerY < 0) playerY = 0;
        if (playerY > SCREEN_HEIGHT - player.height) playerY = SCREEN_HEIGHT - player.height;

        moveCPU(&cpu, &ball);
        moveBall(&ball);

        handleCollision(&ball, &player, playerY, &cpu);
        if (!handleBorderCollision(&ball)) 
            break;

        countText = (char*)malloc(MAX_STRING_SIZE);
        snprintf(countText, MAX_STRING_SIZE, "Count: %d", getScore());

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw paddles and ball
        DrawRectangle(0, (int) playerY, player.width, player.height, player.color);
        DrawRectangle((int) cpu.position.x, (int) cpu.position.y, cpu.entity.width, cpu.entity.height, cpu.entity.color);
        DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);

        sprintf(countText, "Count: %d", getScore());
        DrawText(countText, countX - 14, 0, textSize, WHITE);

        EndDrawing();
    }

    free(countText);
    CloseWindow();

    return 0;
}

void createWindow(Window *window, const char *title, int width, int height) {
    safeStrCopy(window->title, title, sizeof(window->title), &window->titleSize);
    window->height = height;
    window->width = width;
}


