#include "map.h"

#include "utils.h"

#define MAP_TILE_SIZE 16

extern const Map maps[NUM_MAPS];

RenderTile renderTiles[NUM_RENDER_TILES] = {
    {.path = "res/tiles/Grass.png", .frames = 0},
    {.path = "res/tiles/Water.png", .frames = 8},
    {.path = "res/tiles/Start.png", .frames = 0},
    {.path = "res/tiles/FunKey_S.png", .frames = 0},
    {.path = "res/tiles/R_Up.png", .frames = 0},
    {.path = "res/tiles/R_Down.png", .frames = 0},
    {.path = "res/tiles/R_Left.png", .frames = 0},
    {.path = "res/tiles/R_Right.png", .frames = 0},
    {.path = "res/tiles/R_LD.png", .frames = 0},
    {.path = "res/tiles/R_LU.png", .frames = 0},
    {.path = "res/tiles/R_RD.png", .frames = 0},
    {.path = "res/tiles/R_RU.png", .frames = 0},
    {.path = "res/tiles/Sand.png", .frames = 0}
};

void initMap()
{
    for(uint8_t i = 0; i < NUM_RENDER_TILES; i++)
    {
        renderTiles[i].tile = loadPNG(renderTiles[i].path);
    }
}

void quitMap()
{
    //TODO
}

inline LogicTile getTileAtPos(const Map* map, uint8_t x, uint8_t y)
{
    return map->logicTiles[x + y * MAP_WIDTH];
}
bool tileIsReserved(const Map* map, uint8_t x, uint8_t y)
{
    LogicTile t = getTileAtPos(map, x, y);
    return t == U || t == D || t == L || t == R || t == W;
}

void drawMap(SDL_Surface* screen, const Map* map)
{
    static uint8_t animCounter = 0;
    animCounter++;

    for(uint8_t i = 0; i < MAP_WIDTH; i++)
    {
        for(uint8_t j = 0; j < MAP_HEIGHT; j++)
        {
            SDL_Rect pos = {.x = i * MAP_TILE_SIZE, .y = j * MAP_TILE_SIZE};
            uint8_t index = map->displayTiles[i + j * MAP_WIDTH];
            if(renderTiles[index].frames)
            {
                SDL_Rect rect = {.x = (animCounter / MAP_TILE_SIZE % renderTiles[index].frames) * MAP_TILE_SIZE,
                                    .y = 0,
                                    .w = MAP_TILE_SIZE,
                                    .h = MAP_TILE_SIZE};
                SDL_BlitSurface(renderTiles[index].tile, &rect, screen, &pos);
            }
            else
            {
                SDL_BlitSurface(renderTiles[index].tile, NULL, screen, &pos);
            }
        }
    }
}