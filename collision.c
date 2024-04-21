#include "headers/movement.h"
#include <raylib.h>
#include "raylib.h"
#include "headers/window.h"

int score = 0;

void handleCollision(Ball* ball, Entity* player, float playerY, CPU* cpu) {
    if (CheckCollisionCircleRec(ball->position, ball->radius, (Rectangle){0, playerY, player->width, player->height})) {
        score++;
        ball->velocity.x *= -1;
    }

    if (CheckCollisionCircleRec(ball->position, ball->radius, (Rectangle){cpu->position.x, cpu->position.y, cpu->entity.width, cpu->entity.height}))
        ball->velocity.x *= -1; // Reverse the horizontal velocity on collision with CPU's paddle

    if (ball->position.y - ball->radius <= 0 || ball->position.y + ball->radius >= SCREEN_HEIGHT)
        ball->velocity.y *= -1;
}

int handleBorderCollision(Ball* ball) {
    if (ball->position.x - ball->radius < 0 || ball->position.x + ball->radius > SCREEN_WIDTH)
        return 0;

    return 1;
}

int getScore() {
    return score;
}