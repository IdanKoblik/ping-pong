#ifndef PING_PONG_COLLISION_H
#define PING_PONG_COLLISION_H
#include "movement.h"

void handleCollision(Ball* ball, Entity* player, float playerY, CPU* cpu);
int handleBorderCollision(Ball* ball);
int getScore();

#endif //PING_PONG_COLLISION_H
