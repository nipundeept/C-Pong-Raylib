// THIS FILE ANNOUNCES WHICH FUNCTION EXISTS
#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"

//We use pointers so we modify the ACTUAL Paddle and ball, not their copies

void MovePaddle(Paddle *p, bool up, bool down, float dt);
void UpdateBall(Ball *b, Paddle *left, Paddle *right, float dt);

#endif

