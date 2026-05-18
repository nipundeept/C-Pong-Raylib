//MATH LOGIC HERE
#include "logic.h"
#include <math.h>

//Speed constants for the paddle
#define PAD_ACCEL 2400.0f
#define PAD_FRICTION 0.80f

void MovePaddle(Paddle *p, bool up, bool down, float dt) {
    //Apply acceleration
    if (up)         p->velY -= PAD_ACCEL * dt;
    else if (down)  p->velY += PAD_ACCEL * dt;
    else            p->velY *= PAD_FRICTION; //Slow down when no keys are pressed

    //Capping the speed such that it doesn't go infinitely fast
    if (p->velY < -p->speed) p->velY = -p->speed;
    if (p->velY > p->speed)  p->velY = p->speed;

    //Move the paddle
    p->rec.y += p->velY * dt;

    //Edge case: stop it from going off the screen
    if (p->rec.y < 0) {
        p->rec.y = 0;
        p->velY = 0;
    }
    if (p->rec.y + p->rec.height > SCREEN_H) {
        p->rec.y = SCREEN_H - p->rec.height;
        p->velY = 0;
    }
}

void UpdateBall(Ball *b, Paddle *left, Paddle *right, float dt) {
    //record the trail
    b->trail[b->trailHead] = b->pos;
    b->trailHead = (b->trailHead + 1) % TRAIL_LEN;
    //Move the ball
    b->pos.x += b->spd.x * dt;
    b->pos.y += b->spd.y * dt;

    //Bounce off top and bottom walls
    if (b->pos.y <= b->radius) {
        b->pos.y = b->radius;
        b->spd.y *= -1.0f; //Reverse Y direction
    }
    if (b->pos.y >= SCREEN_H - b->radius) {
        b->pos.y = SCREEN_H - b->radius;
        b->spd.y *= -1.0f; //Reverse Y direction
    }

    //Bounce off paddles (using Raylib's built-in collection checker)
    if (CheckCollisionCircleRec(b->pos, b->radius, left->rec)) {
        b->pos.x = left->rec.x + left->rec.width + b->radius; //push it out of the paddle
        b->spd.x = fabsf(b->spd.x); //force it to go right
    }
    if (CheckCollisionCircleRec(b->pos, b->radius, right->rec)) {
        b->pos.x = right->rec.x - b->radius; // Push it out
        b->spd.x = -fabsf(b->spd.x); // Force it to go left
    }
}