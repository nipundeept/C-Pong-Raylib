#include "raylib.h"

//We define our screen size as symbolic constants at the top
#define SCREEN_W 800
#define SCREEN_H 450

int main(void) {
    //Initialisation
    InitWindow(SCREEN_W, SCREEN_H, "PONG // NEON EDITION");

    SetTargetFPS(60);
    //GAME LOOP
    //WindowShouldClose() returns true if the user presses ESC or the 'X' button
    while (!WindowShouldClose()) {
        //UPDATE

        //DRAW
        BeginDrawing();

        ClearBackground((Color){3, 3, 18, 255});

        //Neon graphics to be drawn here
        EndDrawing();
    }
    //De-initialisation -> cleans up memory and closes the window safely
    CloseWindow();
    return 0;
}