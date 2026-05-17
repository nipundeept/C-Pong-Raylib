#ifndef TYPES_H //Header Guard
#define TYPES_H

#include "raylib.h"

//Constants used across the game
#define MAX_NAME 16
#define TRAIL_LEN 14

//defining ENUMS (user-defined data type), which gives meaning to an integer literal and makes readability
typedef enum {
    ST_NAME_P1 = 0,
    ST_MODE_SELECT,
    ST_NAME_P2,
    ST_DIFFICULTY,
    ST_COUNTDOWN,
    ST_PLAYING,
    ST_PAUSED,
    ST_ROUND_OVER,
    ST_GAME_OVER
} GameState;

typedef enum {
    MODE_1V1 = 0, MODE_AI
} GameMode;

typedef enum {
    EASY = 0,
    MEDIUM,
    HARD,
    DIFF_COUNT
} Difficulty;

typedef struct {
    Rectangle rec; // Raylib struct holding x, y, width and height
    float speed; //maximum speed movement
    float velY; //current velocity
    float prevY; //Where the paddle was last frame (used to calculate ball spin)
    int score;
    char name[MAX_NAME + 1];
    Color col; //Raylib struct for RGBA colours
} Paddle;

typedef struct {
    Vector2 pos; //position in x, y coordinate (Raylib structure)
    Vector2 spd; //Veclocity in both x and y directions.
    int radius;
    bool fireball; //is the fireball powerup active?
    float fireTimer; // how much longer the fireball lasts
    Vector2 trail[TRAIL_LEN]; //Array to store previous positions for the neon trail effect
    int trailHead;
} Ball;

#endif // TYPES_H
