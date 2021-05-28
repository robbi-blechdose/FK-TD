#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>
#include <SDL/SDL.h>

#define NUM_MAP_TILES 5
typedef enum {
    G, W, P, S, E
} Tile;

#define MAP_WIDTH  15
#define MAP_HEIGHT 12

typedef struct {
    Tile tiles[MAP_WIDTH * MAP_HEIGHT];
} Map;

extern Map maps[1];

uint8_t tileIsPath(Map* map, uint8_t x, uint8_t y);
uint8_t tileIsEnd(Map* map, uint8_t x, uint8_t y);

#endif