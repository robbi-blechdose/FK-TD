#include "map.h"

Map maps[1] = {
    {
        .tiles = {
        G, S, G, G, G, G, G, G, G, G, G, G, G, E, G,
        G, P, G, G, G, G, G, G, G, G, G, G, G, P, G,
        G, P, G, G, G, G, G, G, G, G, G, G, G, P, G,
        G, P, G, G, G, G, G, G, G, G, G, G, P, P, G,
        G, P, G, P, P, P, P, G, G, G, G, G, P, G, G,
        G, P, G, P, G, G, P, G, G, G, G, G, P, P, G,
        G, P, G, P, G, G, P, G, G, G, G, G, G, P, G,
        G, P, G, P, G, P, P, G, G, G, G, G, G, P, G,
        G, P, G, P, G, P, G, G, G, G, G, G, G, P, G,
        G, P, G, P, G, P, G, G, G, G, G, G, G, P, G,
        G, P, P, P, G, P, P, P, P, P, P, P, P, P, G,
        G, G, G, G, G, G, G, G, G, G, G, G, G, G, G}
    }
};

Tile getTileAtPos(Map* map, uint8_t x, uint8_t y)
{
    return map->tiles[x + y * MAP_WIDTH];
}

uint8_t tileIsPath(Map* map, uint8_t x, uint8_t y)
{
    if(getTileAtPos(map, x, y) == P || getTileAtPos(map, x, y) == E)
    {
        return 1;
    }
    return 0;
}

uint8_t tileIsEnd(Map* map, uint8_t x, uint8_t y)
{
    if(getTileAtPos(map, x, y) == E)
    {
        return 1;
    }
    return 0;
}