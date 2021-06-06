#include "map.h"

Map maps[1] = {
    {
        .tiles = {
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
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G}
    }
};

Tile getTileAtPos(Map* map, uint8_t x, uint8_t y)
{
    return map->tiles[x + y * MAP_WIDTH];
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
    Tile t = getTileAtPos(map, x, y);
    if(t == U || t == D || t == L || t == R || t == S || t == E || t == W)
    {
        return 1;
    }
    return 0;
}