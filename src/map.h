#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>
#include <SDL/SDL.h>

#define NUM_MAP_TILES 8
typedef enum {
    G, W, S, E,
    U, D, L, R
} Tile;

#define MAP_WIDTH  15
#define MAP_HEIGHT 12

typedef struct {
    Tile tiles[MAP_WIDTH * MAP_HEIGHT];
} Map;

extern Map maps[1];

Tile getTileAtPos(Map* map, uint8_t x, uint8_t y);
uint8_t tileIsEnd(Map* map, uint8_t x, uint8_t y);
uint8_t tileIsReserved(Map* map, uint8_t x, uint8_t y);

#endif