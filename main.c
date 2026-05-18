#include "raylib.h"
#include "types.h" //Includes new custom types
#include "logic.h" //Includes logic menu

int main(void) {
    //Initialisation
    InitWindow(SCREEN_W, SCREEN_H, "PONG // NEON EDITION");

    SetTargetFPS(60);
    // CREATING OUR GAME OBJECTS
    GameState state = ST_PLAYING; //skipping menus for now

    Paddle leftPaddle = {0};
    leftPaddle.rec = (Rectangle){ 50, SCREEN_H/2.0f - 50, 18, 100}; // x, y, width, height
    leftPaddle.col = (Color){ 0, 230, 255, 255}; //Cyan
    leftPaddle.speed = 430.0f; //Give paddles speed

    Paddle rightPaddle = {0};
    rightPaddle.rec = (Rectangle){ SCREEN_W - 68, SCREEN_H/2.0f - 50, 18, 100};
    rightPaddle.col = (Color){ 255, 20, 200, 255}; //Magenta
    rightPaddle.speed = 430.0f; //Give paddles speed

    Ball ball = {0};
    ball.pos = (Vector2) {SCREEN_W / 2.0f, SCREEN_H / 2.0f}; //Center of the screen
    ball.radius = 10;
    ball.spd = (Vector2) { 320.0f, 200.0f}; //give ball starting velocity
    //WindowShouldClose() returns true if the user presses ESC or the 'X' button
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        //---UPDATE---
        //WE CALL OUR LOGIC FUNCTIONS
        //Player 1 controls (W and S)
        MovePaddle(&leftPaddle, IsKeyDown(KEY_W), IsKeyDown(KEY_S), dt);

        //Player 2 controls (Up Arrow and Down Arrow)
        MovePaddle(&rightPaddle, IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN), dt);

        //Update the ball
        UpdateBall(&ball, &leftPaddle, &rightPaddle, dt);

        //DRAW
        BeginDrawing();

        ClearBackground((Color){3, 3, 18, 255});
        //Drawing basic shapes to test
        DrawRectangleRec(leftPaddle.rec, leftPaddle.col);
        DrawRectangleRec(rightPaddle.rec, rightPaddle.col);
        DrawCircleV(ball.pos, ball.radius, WHITE);

        EndDrawing();
    }
    //De-initialisation -> cleans up memory and closes the window safely
    CloseWindow();
    return 0;
}