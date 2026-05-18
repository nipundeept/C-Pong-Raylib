//
// Created by Nipun Deept on 18/05/26.
//
#include "graphics.h"
#include "raylib.h"

void DrawGame(Paddle *left, Paddle *right, Ball *ball) {
    BeginDrawing();

    // The dark blue background
    ClearBackground((Color){3, 3, 18, 255});

    // Draw the scores
    DrawText(TextFormat("%d", left->score), SCREEN_W/4, 20, 60, WHITE);
    DrawText(TextFormat("%d", right->score), 3*SCREEN_W/4, 20, 60, WHITE);

    // Draw the paddles and ball
    DrawRectangleRec(left->rec, left->col);
    DrawRectangleRec(right->rec, right->col);
    DrawCircleV(ball->pos, ball->radius, WHITE);

    EndDrawing();
}