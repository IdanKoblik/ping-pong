#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "strutils.h"

#define MAX_STRING_SIZE 256

typedef struct {
    int width;
    int height;
    char title[MAX_STRING_SIZE];
    size_t titleSize;
} Window;

typedef struct {
    int width;
    int height;
    Color color;
} Entity;

typedef struct {
    float radius;
    Color color;
    struct Vector2 position;
    struct Vector2 velocity;
} Ball;

typedef struct {
    Entity entity;
    struct Vector2 position;
} CPU;

void createWindow(Window *window, const char *title, int width, int height);

int main() {
    Window gameWindow;
    const int width = 800;
    const int height = 450;
    const char TITLE[] = "Ping-Pong game";

    createWindow(&gameWindow, TITLE, width, height);
    InitWindow(gameWindow.width, gameWindow.height, gameWindow.title);

    float playerY = height / 2 - 25;
    float playerSpeed = 0.05f;

    const int entityWidth = 10;
    const int entityHeight = 50;
    const Color entityColor = WHITE;
    Entity player = {entityWidth, entityHeight, entityColor};
    CPU cpu = {{entityWidth, entityHeight, entityColor}, {width - entityWidth, height / 2 - 25}};

    const float speed = 0.04;
    Ball ball = {10, entityColor, {width / 2, height / 2}, {speed, speed}};

    int count = 0;
    const int textSize = 20;
    const int countX = width / 2 - textSize;
    char* countText = NULL;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) playerY -= playerSpeed;
        if (IsKeyDown(KEY_S)) playerY += playerSpeed;

        if (playerY < 0) playerY = 0;
        if (playerY > height - player.height) playerY = height - player.height;

        // CPU movement logic
        if (ball.position.y < cpu.position.y + cpu.entity.height / 2)
            cpu.position.y -= playerSpeed;
        else
            cpu.position.y += playerSpeed;

        if (cpu.position.y < 0) cpu.position.y = 0;
        if (cpu.position.y > height - cpu.entity.height) cpu.position.y = height - cpu.entity.height;

        ball.position.x += ball.velocity.x;
        ball.position.y += ball.velocity.y;

        // Ball and paddles collision check
        if (CheckCollisionCircleRec(ball.position, ball.radius, (Rectangle){0, playerY, player.width, player.height})) {
            count++;
            ball.velocity.x *= -1;
        }

        if (CheckCollisionCircleRec(ball.position, ball.radius, (Rectangle){cpu.position.x, cpu.position.y, cpu.entity.width, cpu.entity.height}))
            ball.velocity.x *= -1; // Reverse the horizontal velocity on collision with CPU's paddle

        if (ball.position.y - ball.radius <= 0 || ball.position.y + ball.radius >= height)
            ball.velocity.y *= -1;

        if (ball.position.x - ball.radius < 0 || ball.position.x + ball.radius > width)
            CloseWindow();

        free(countText);
        countText = (char*)malloc(MAX_STRING_SIZE);
        snprintf(countText, MAX_STRING_SIZE, "Count: %d", count);

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw paddles and ball
        DrawRectangle(0, (int) playerY, player.width, player.height, player.color);
        DrawRectangle((int) cpu.position.x, (int) cpu.position.y, cpu.entity.width, cpu.entity.height, cpu.entity.color);
        DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);

        sprintf(countText, "Count: %d", count);
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


