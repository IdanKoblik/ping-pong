#ifndef PING_PONG_MOVEMENT_H
#define PING_PONG_MOVEMENT_H
#include <raylib.h>

#define TARGET_FPS 60
#define DELTA 1 
#define ENTITY_SPEED 300

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

void moveCPU(CPU* cpu, Ball* ball);

void moveBall(Ball* ball);

float getDeltaSpeed();

#endif //PING_PONG_MOVEMENT_H
