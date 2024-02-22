#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#include "engine/math.h"

#define NUM_RENDER_TILES 13
//TODO: remove start tile, replace with position in map struct
//that would allow arbitrary starting directions instead of only down
typedef enum {
    G, W,
    U, D, L, R,
    NUM_LOGIC_TILES
} LogicTile;

typedef struct {
    char* path;
    uint8_t frames;
    SDL_Surface* tile;
} RenderTile;

#define MAP_WIDTH  15
#define MAP_HEIGHT 12

typedef struct {
    uint8_t displayTiles[MAP_WIDTH * MAP_HEIGHT];
    LogicTile logicTiles[MAP_WIDTH * MAP_HEIGHT];
    vec2i startPosition;
    vec2i endPosition;
} Map;

#define NUM_MAPS 6
extern const Map maps[NUM_MAPS];

void initMap();
void quitMap();

LogicTile getTileAtPos(Map* map, uint8_t x, uint8_t y);
bool tileIsReserved(Map* map, uint8_t x, uint8_t y);

void drawMap(SDL_Surface* screen, Map* map);

#endif