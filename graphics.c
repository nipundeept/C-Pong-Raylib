//
// Created by Nipun Deept on 18/05/26.
//
#include "graphics.h"
#include "raylib.h"

// --- NEON PALETTE ---
#define COL_BG        ((Color){  3,  3, 18, 255})
#define COL_GRID      ((Color){ 14, 14, 48, 255})
#define COL_UI        ((Color){  0, 255, 200, 255})

// Helper function to easily change the transparency (alpha) of a color
static Color Alpha(Color c, unsigned char a) {
    c.a = a;
    return c;
}

// Helper: Draws a cyberpunk grid with a dark vignette border
static void DrawBackground(void) {
    ClearBackground(COL_BG);

    // Draw the grid lines
    for (int x = 0; x <= SCREEN_W; x += 40) DrawLine(x, 0, x, SCREEN_H, COL_GRID);
    for (int y = 0; y <= SCREEN_H; y += 40) DrawLine(0, y, SCREEN_W, y, COL_GRID);

    // Draw the dark vignette borders
    for (int i = 1; i <= 7; i++) {
        unsigned char a = (unsigned char)(50 / i);
        DrawRectangle(0, 0, i*10, SCREEN_H, (Color){0,0,0,a});
        DrawRectangle(SCREEN_W-i*10, 0, i*10, SCREEN_H, (Color){0,0,0,a});
        DrawRectangle(0, 0, SCREEN_W, i*7,  (Color){0,0,0,a});
        DrawRectangle(0, SCREEN_H-i*7, SCREEN_W, i*7,  (Color){0,0,0,a});
    }

    // Draw glowing center dashed line
    for (int y = 0; y < SCREEN_H; y += 22) {
        DrawRectangle(SCREEN_W/2-1, y, 2, 12, Alpha(COL_UI, 55));
    }
}

// Helper: Soft glow around a rectangle
static void DrawGlowRect(Rectangle rec, Color c) {
    // Faint outer glows
    DrawRectangle((int)rec.x-9, (int)rec.y-5, (int)rec.width+18, (int)rec.height+10, Alpha(c, 12));
    DrawRectangle((int)rec.x-5, (int)rec.y-3, (int)rec.width+10, (int)rec.height+ 6, Alpha(c, 30));
    DrawRectangle((int)rec.x-2, (int)rec.y-1, (int)rec.width+ 4, (int)rec.height+ 2, Alpha(c, 70));

    // Solid core
    DrawRectangleRec(rec, c);

    // Bright specular highlight stripe on the inside
    DrawRectangle((int)rec.x+2, (int)rec.y+5, 3, (int)rec.height-10, Alpha(WHITE, 55));
}

// Helper: Soft glow around a circle
static void DrawGlowCirc(Vector2 p, float r, Color c) {
    // Faint outer glows
    DrawCircleV(p, r + 16, Alpha(c, 12));
    DrawCircleV(p, r + 10, Alpha(c, 28));
    DrawCircleV(p, r +  5, Alpha(c, 60));
    DrawCircleV(p, r +  2, Alpha(c,120));

    // Solid core
    DrawCircleV(p, r, c);

    // Bright white-ish center
    DrawCircleV(p, r * 0.4f, Alpha(WHITE, 200));
}

// --- MAIN DRAW FUNCTION ---
void DrawGame(Paddle *left, Paddle *right, Ball *ball) {
    BeginDrawing();

    // 1. Draw Background
    DrawBackground();

    // 2. Draw HUD (Scores)
    DrawText(TextFormat("%d", left->score), SCREEN_W/4 - 20, 20, 60, left->col);
    DrawText(TextFormat("%d", right->score), 3*SCREEN_W/4 - 20, 20, 60, right->col);

    // 3. Draw Game Objects using our new neon helpers!
    DrawGlowRect(left->rec, left->col);
    DrawGlowRect(right->rec, right->col);
    // --- DRAW TRAIL ---
    for (int i = 1; i < TRAIL_LEN; i++) {
        // Math to find the index of older positions in our circular buffer
        int idx = (ball->trailHead - i + TRAIL_LEN) % TRAIL_LEN;

        // Calculate a fraction (0.0 to 1.0) based on how old this position is
        float frac = 1.0f - (float)i / TRAIL_LEN;

        // Make the color fade out the older it gets
        Color trailColor = WHITE;
        trailColor.a = (unsigned char)(frac * frac * 160.0f);

        // Draw the trail dot, scaling it down based on age
        DrawCircleV(ball->trail[idx], (float)ball->radius * frac * 0.85f, trailColor);
    }
    DrawGlowCirc(ball->pos, ball->radius, WHITE);

    EndDrawing();
}