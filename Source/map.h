#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "math.h"

enum movementStates; // Types of state to move on map

// City on map
typedef struct City
{
    char *name;
    Vector2 pos;
    Rectangle model;
    Texture2D texture;
} City;

// Player on map
typedef struct PlayerState
{
    Vector2 pos;       // Current pos on map
    Vector2 prevpos;   // Previous pos on map
    Rectangle model;   // Model to draw
    Texture2D texture; // Texture for model
} PlayerState;

// Keep things about map state
typedef struct MapState
{
    City *current;     // Start City
    City *destination; // Destination City
} MapState;

// Map is few rectangles with textures on it
// Keep Maps drawing things
typedef struct Map
{
    Rectangle bg;        // BG rectangle
    Texture2D bgTexture; // BG texture
    Texture2D roads;     // Road Texture
} Map;

// Main loop. Update + Render
void mapLoop(enum gameState *state);

// Find next pixel to move
void updateMovement(PlayerState *plSt, Color *roads, MapState *mapSt);

// Draw player on map
void drawPlayer(PlayerState *plSt);

#endif