#include "map.h"

const Map maps[NUM_MAPS] = {
    //By Robbi
    {
        .displayTiles = {
        0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
        0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
        0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
        0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 0,
        0, 5, 0, 10, 7, 7, 8, 0, 0, 0, 0, 0, 4, 0, 0,
        0, 5, 0, 4, 0, 0, 5, 0, 0, 0, 0, 0, 11, 8, 0,
        0, 5, 0, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0, 4, 0,
        0, 5, 0, 4, 0, 10, 9, 0, 1, 1, 1, 1, 0, 4, 0,
        0, 5, 0, 4, 0, 11, 8, 0, 1, 1, 1, 1, 0, 4, 0,
        0, 5, 0, 4, 0, 0, 5, 0, 1, 1, 1, 1, 0, 4, 0,
        0, 11, 7, 9, 0, 0, 11, 7, 7, 7, 7, 7, 7, 9, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        .logicTiles = {
        G, S, G, G, G, G, G, G, G, G, G, G, G, E, G,
        G, D, G, G, G, G, G, G, G, G, G, G, G, U, G,
        G, D, G, G, G, G, G, G, G, G, G, G, G, U, G,
        G, D, G, G, G, G, G, G, G, G, G, G, R, U, G,
        G, D, G, R, R, R, D, G, G, G, G, G, U, G, G,
        G, D, G, U, G, G, D, G, G, G, G, G, U, L, G,
        G, D, G, U, G, G, D, G, G, G, G, G, G, U, G,
        G, D, G, U, G, D, L, G, W, W, W, W, G, U, G,
        G, D, G, U, G, R, D, G, W, W, W, W, G, U, G,
        G, D, G, U, G, G, D, G, W, W, W, W, G, U, G,
        G, R, R, U, G, G, R, R, R, R, R, R, R, U, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G
        }
    },
    {
        .displayTiles = {
        1, 1, 1, 2, 0, 10, 7, 8, 0, 0, 0, 0, 0, 3, 0,
        1, 10, 8, 11, 7, 9, 0, 5, 0, 10, 7, 7, 7, 9, 0,
        1, 5, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0,
        1, 5, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0,
        1, 5, 11, 6, 6, 6, 6, 9, 0, 4, 0, 0, 12, 12, 12,
        1, 5, 1, 12, 12, 0, 0, 0, 0, 4, 0, 0, 12, 12, 12,
        1, 5, 1, 12, 12, 0, 0, 0, 0, 4, 0, 0, 12, 12, 12,
        1, 5, 1, 1, 12, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
        1, 5, 1, 1, 12, 0, 0, 0, 0, 11, 6, 6, 6, 8, 0,
        12, 5, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
        0, 11, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        .logicTiles = {
        W, W, W, S, G, R, R, D, G, G, G, G, G, E, G,
        W, D, L, R, R, U, G, D, G, R, R, R, R, U, G,
        W, D, U, G, G, G, G, D, G, U, G, G, G, G, G,
        W, D, U, G, G, G, G, D, G, U, G, G, G, G, G,
        W, D, U, L, L, L, L, L, G, U, G, G, G, G, G,
        W, D, W, G, G, G, G, G, G, U, G, G, G, G, G,
        W, D, W, G, G, G, G, G, G, U, G, G, G, G, G,
        W, D, W, W, G, G, G, G, G, U, G, G, G, G, G,
        W, D, W, W, G, G, G, G, G, U, L, L, L, L, G,
        G, D, G, G, G, G, G, G, G, G, G, G, G, U, G,
        G, R, R, R, R, R, R, R, R, R, R, R, R, U, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G
        }
    },
    //By Rinkuji
    {
        .displayTiles = {
        0, 0, 0, 0, 0, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0,
        0, 10, 8, 0, 0, 0, 5, 0, 4, 0, 0, 0, 10, 8, 0,
        0, 5, 11, 8, 0, 0, 5, 0, 4, 0, 0, 10, 9, 4, 0,
        0, 5, 0, 11, 8, 0, 5, 0, 4, 0, 10, 9, 0, 4, 0,
        0, 11, 8, 0, 11, 8, 5, 0, 4, 10, 9, 0, 10, 9, 0,
        0, 0, 11, 8, 0, 11, 9, 0, 11, 9, 0, 10, 9, 0, 0,
        0, 0, 0, 11, 7, 7, 8, 0, 10, 7, 7, 9, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0,
        12, 12, 0, 10, 6, 6, 9, 0, 11, 6, 6, 8, 0, 0, 0,
        1, 1, 12, 5, 12, 10, 7, 7, 7, 8, 12, 4, 12, 12, 12,
        1, 1, 1, 11, 7, 9, 1, 1, 1, 11, 7, 9, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        .logicTiles = {
        G, G, G, G, G, G, S, G, E, G, G, G, G, G, G,
        G, D, L, G, G, G, D, G, U, G, G, G, D, L, G,
        G, D, U, L, G, G, D, G, U, G, G, D, L, U, G,
        G, D, G, U, L, G, D, G, U, G, D, L, G, U, G,
        G, R, D, G, U, L, D, G, U, D, L, G, R, U, G,
        G, G, R, D, G, U, L, G, U, L, G, R, U, G, G,
        G, G, G, R, R, R, D, G, R, R, R, U, G, G, G,
        G, G, G, G, G, G, D, G, U, G, G, G, G, G, G,
        G, G, G, D, L, L, L, G, U, L, L, L, G, G, G,
        G, G, G, D, G, R, R, R, R, D, G, U, G, G, G,
        G, G, G, R, R, U, G, G, G, R, R, U, G, G, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G
        }
    },
    //By V13Loca
    {
        .displayTiles = {
        0, 0, 0, 0, 0, 0, 0, 12, 12, 1, 1, 12, 0, 0, 0,
        0, 10, 6, 8, 0, 2, 0, 12, 1, 1, 1, 12, 0, 3, 0,
        0, 5, 0, 4, 0, 5, 0, 12, 1, 1, 12, 12, 0, 4, 0,
        0, 5, 0, 4, 0, 5, 12, 12, 1, 1, 12, 12, 12, 4, 0,
        0, 5, 0, 11, 6, 9, 12, 12, 1, 1, 1, 12, 12, 4, 12,
        0, 5, 0, 0, 0, 0, 12, 1, 1, 1, 1, 1, 1, 4, 1,
        0, 5, 0, 0, 0, 12, 12, 1, 1, 1, 1, 1, 1, 4, 1,
        0, 11, 7, 7, 8, 12, 12, 1, 1, 1, 12, 12, 12, 4, 12,
        0, 0, 0, 0, 5, 12, 1, 1, 1, 12, 12, 12, 0, 4, 0,
        0, 0, 0, 0, 11, 7, 7, 7, 7, 7, 8, 0, 0, 4, 0,
        0, 0, 0, 12, 12, 1, 1, 1, 12, 12, 11, 7, 7, 9, 0,
        0, 0, 12, 12, 1, 1, 1, 12, 12, 0, 0, 0, 0, 0, 0,
        },
        .logicTiles = {
        G, G, G, G, G, G, G, G, G, W, W, G, G, G, G,
        G, D, L, L, G, S, G, G, W, W, W, G, G, E, G,
        G, D, G, U, G, D, G, G, W, W, G, G, G, U, G,
        G, D, G, U, G, D, G, G, W, W, G, G, G, U, G,
        G, D, G, U, L, L, G, G, W, W, W, G, G, U, G,
        G, D, G, G, G, G, G, W, W, W, W, W, W, U, W,
        G, D, G, G, G, G, G, W, W, W, W, W, W, U, W,
        G, R, R, R, D, G, G, W, W, W, G, G, G, U, G,
        G, G, G, G, D, G, W, W, W, G, G, G, G, U, G,
        G, G, G, G, R, R, R, R, R, R, D, G, G, U, G,
        G, G, G, G, G, G, W, W, W, G, R, R, R, U, G,
        G, G, G, G, G, W, W, W, G, G, G, G, G, G, G,
        }
    },
    {
        .displayTiles = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 10, 9, 0, 10, 6, 6, 6, 6, 6, 6, 6, 8, 0, 0,
        0, 5, 0, 10, 9, 0, 0, 0, 0, 0, 0, 0, 11, 8, 0,
        0, 5, 0, 5, 0, 10, 6, 6, 6, 6, 6, 8, 0, 4, 0,
        0, 5, 0, 5, 0, 5, 0, 0, 0, 0, 0, 4, 0, 4, 0,
        0, 5, 0, 5, 0, 11, 7, 7, 7, 3, 0, 4, 0, 4, 0,
        0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0,
        0, 5, 0, 11, 7, 7, 7, 7, 7, 7, 7, 9, 0, 4, 0,
        0, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 0,
        0, 0, 11, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        .logicTiles = {
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G,
        G, G, S, G, G, G, G, G, G, G, G, G, G, G, G,
        G, D, L, G, D, L, L, L, L, L, L, L, L, G, G,
        G, D, G, D, L, G, G, G, G, G, G, G, U, L, G,
        G, D, G, D, G, D, L, L, L, L, L, L, G, U, G,
        G, D, G, D, G, D, G, G, G, G, G, U, G, U, G,
        G, D, G, D, G, R, R, R, R, E, G, U, G, U, G,
        G, D, G, D, G, G, G, G, G, G, G, U, G, U, G,
        G, D, G, R, R, R, R, R, R, R, R, U, G, U, G,
        G, R, D, G, G, G, G, G, G, G, G, G, R, U, G,
        G, G, R, R, R, R, R, R, R, R, R, R, U, G, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G
        }
    },
    {
        .displayTiles = {
        0, 12, 12, 1, 1, 12, 0, 0, 0, 0, 0, 0, 12, 1, 1,
        0, 2, 12, 1, 1, 12, 0, 10, 7, 7, 7, 8, 0, 12, 1,
        0, 5, 12, 1, 1, 12, 10, 9, 12, 12, 12, 11, 8, 12, 1,
        0, 5, 12, 1, 1, 12, 4, 12, 12, 1, 1, 12, 5, 12, 12,
        0, 5, 0, 12, 1, 12, 11, 8, 12, 1, 1, 12, 5, 0, 12,
        0, 11, 8, 0, 12, 12, 0, 4, 12, 12, 12, 0, 5, 0, 12,
        0, 0, 11, 8, 0, 0, 10, 9, 0, 0, 0, 10, 9, 0, 12,
        12, 12, 0, 11, 7, 7, 9, 10, 6, 6, 6, 9, 0, 12, 12,
        12, 12, 12, 12, 0, 0, 0, 5, 0, 0, 0, 0, 0, 12, 1,
        1, 1, 1, 12, 12, 12, 0, 5, 0, 0, 0, 0, 12, 1, 1,
        1, 1, 1, 1, 1, 12, 12, 11, 7, 7, 7, 7, 7, 3, 1,
        1, 1, 1, 1, 1, 1, 12, 12, 0, 0, 0, 0, 12, 1, 1
        },
        .logicTiles = {
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G,
        G, S, G, G, G, G, G, R, R, R, R, D, G, G, G,
        G, D, G, G, G, G, R, U, G, G, G, R, D, G, G,
        G, D, G, G, G, G, U, G, G, G, G, G, D, G, G,
        G, D, G, G, G, G, U, L, G, G, G, G, D, G, G,
        G, R, D, G, G, G, G, U, G, G, G, G, D, G, G,
        G, G, R, D, G, G, R, U, G, G, G, D, L, G, G,
        G, G, G, R, R, R, U, D, L, L, L, L, G, G, G,
        G, G, G, G, G, G, G, D, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, D, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, R, R, R, R, R, R, E, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G
        }
    }
};

LogicTile getTileAtPos(Map* map, uint8_t x, uint8_t y)
{
    return map->logicTiles[x + y * MAP_WIDTH];
}

uint8_t tileIsEnd(Map* map, uint8_t x, uint8_t y)
{
    if(getTileAtPos(map, x, y) == E)
    {
        return 1;
    }
    return 0;
}

uint8_t tileIsReserved(Map* map, uint8_t x, uint8_t y)
{
    LogicTile t = getTileAtPos(map, x, y);
    if(t == U || t == D || t == L || t == R || t == S || t == E || t == W)
    {
        return 1;
    }
    return 0;
}

Point getStartPos(Map* map)
{
    for(uint8_t i = 0; i < MAP_WIDTH; i++)
    {
        for(uint8_t j = 0; j < MAP_HEIGHT; j++)
        {
            if(map->logicTiles[i + j * MAP_WIDTH] == S)
            {
                Point p = {.x = i, .y = j};
                return p;
            }
        }
    }
    return (Point) {.x = 0, .y = 0};
}