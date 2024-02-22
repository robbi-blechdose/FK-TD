#include "hud.h"

#include <SDL_gfxPrimitives.h>

SDL_Surface* cursorTile;

//TODO: replace with automatic layout
HUDElement hudElements[NUM_TOWER_TYPES] = {
    {.tower = 0, .position = {.x = 0, .y = 12 * 16}, .name = "Zap"},
    {.tower = 1, .position = {.x = 48, .y = 12 * 16}, .name = "Ice"},
    {.tower = 2, .position = {.x = 96, .y = 12 * 16}, .name = "Fire"},
    {.tower = 3, .position = {.x = 96 + 56, .y = 12 * 16}, .name = "Cannon"}
};

void initHUD()
{
    cursorTile = loadPNG("res/Cursor.png");
}

void drawHUD(SDL_Surface* screen, Game* game)
{
    boxRGBA(screen, 0, 12 * 16, 240, 240, 160, 82, 40, 255);

    char buffer[64];

    for(uint8_t i = 0; i < NUM_TOWER_TYPES; i++)
    {
        SDL_Rect rect = {.x = 0, .y = 0, .w = 16, .h = 16};
        //SDL_BlitSurface(towerTiles[i], &rect, screen, &hudElements[i].position);
        stringRGBA(screen, hudElements[i].position.x + 16, hudElements[i].position.y, hudElements[i].name, 255, 255, 255, 255);
        //sprintf(buffer, "%d$", towerTypes[i].cost);
        stringRGBA(screen, hudElements[i].position.x + 16, hudElements[i].position.y + 8, buffer, 255, 255, 255, 255);
    }
    //Stats
    if(game->waveActive)
    {
        sprintf(buffer, "Wave:%d | %d$ | %d <3", game->wave, game->money, game->lives);
    }
    else
    {
        sprintf(buffer, "Next:%d | %d$ | %d <3", game->wave + 1, game->money, game->lives);
    }
    stringRGBA(screen, 0, 230, buffer, 255, 255, 255, 255);
}

void drawCursor(SDL_Surface* screen, vec2i* cursor, uint8_t cursorMode, TowerType selectedTower)
{
    if(cursorMode == CURSOR_MAP)
    {
        SDL_Rect pos = {.x = cursor->x * 16, .y = cursor->y * 16};
        if(selectedTower != TT_NONE)
        {
            vec2i position = {.x = pos.x, .y = pos.y};
            drawTowerWithRange(screen, selectedTower, position);
        }
        SDL_BlitSurface(cursorTile, NULL, screen, &pos);
    }
    else
    {
        uint8_t index = cursor->x + cursor->y; //TODO
        SDL_Rect pos = {.x = hudElements[index].position.x, .y = hudElements[index].position.y};
        SDL_BlitSurface(cursorTile, NULL, screen, &pos);
    }
}