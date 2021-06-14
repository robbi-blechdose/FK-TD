#include "map.h"

Map maps[1] = {
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