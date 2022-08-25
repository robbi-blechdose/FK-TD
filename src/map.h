#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#include "utils.h"

#define NUM_RENDER_TILES 13
#define NUM_LOGIC_TILES 8
typedef enum {
    G, W, S, E,
    U, D, L, R
} LogicTile;

#define MAP_WIDTH  15
#define MAP_HEIGHT 12

typedef struct {
    uint8_t displayTiles[MAP_WIDTH * MAP_HEIGHT];
    LogicTile logicTiles[MAP_WIDTH * MAP_HEIGHT];
} Map;

#define NUM_MAPS 6
extern const Map maps[NUM_MAPS];

LogicTile getTileAtPos(Map* map, uint8_t x, uint8_t y);
bool tileIsEnd(Map* map, uint8_t x, uint8_t y);
bool tileIsReserved(Map* map, uint8_t x, uint8_t y);
Point getStartPos(Map* map);

#endif