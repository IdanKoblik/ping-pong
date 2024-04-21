#include "headers/movement.h"
#include "headers/window.h"

void moveCPU(CPU* cpu, Ball* ball) {
    // CPU movement logic
    if (ball->position.y < cpu->position.y + cpu->entity.height / 2)
        cpu->position.y -= getDeltaSpeed();
    else
        cpu->position.y += getDeltaSpeed();

    if (cpu->position.y < 0) cpu->position.y = 0;
    if (cpu->position.y > SCREEN_HEIGHT - cpu->entity.height) cpu->position.y = SCREEN_HEIGHT - cpu->entity.height;
}

void moveBall(Ball* ball) {
    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;
}

float getDeltaSpeed() {
    return ENTITY_SPEED * DELTA / TARGET_FPS;
}