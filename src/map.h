#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>
#include <SDL/SDL.h>

#define NUM_MAP_TILES 5
typedef enum {
    G, W, P, S, E
} Tile;

typedef struct {
    Tile tiles[15 * 12];
} Map;

extern Map maps[1];

#endif