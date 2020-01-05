#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "gamemath.h"
#include "list.h"
#include "logger.h"

#define MAX_ROAD_NAME 128

enum movementStates; // Types of state to move on map

// One road with two end points and array of point to move
typedef struct Road
{
    int pointCount;      // Number of points to move
    char *name;          // Road name in config file
    Vector2 *points;     // Point on map to move
    Vector2 firstPoint;  // First point on map
    Vector2 secondPoint; // Second point on map
} Road;

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
    int currentPosInMap;
    Road *road;
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

// Start movement. Set player position
void startMovement(PlayerState *plSt, Road *road);

// Find next pixel to move
void updateMovement(PlayerState *plSt);

// Draw player on map
void drawPlayer(PlayerState *plSt);

// Take start, end point + convert pixels image as Vector2 path
Road processRoad(char *roadname);

// x, y convert to index on image. Return -1 if pos doesnot exist
int coordToIndexConvert(int x, int y, int width, int height);


#endif