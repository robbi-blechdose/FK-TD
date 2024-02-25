#include "hud.h"

#include <SDL_gfxPrimitives.h>

//TODO: rename current HUD to buy menu
//TODO: add tower upgrade menu

//TODO: move cursor calculations into here form main.c

SDL_Surface* cursorTile;

#define HUD_BUY_TOWERS_PER_LINE 4

void initHUD()
{
    cursorTile = loadPNG("res/Cursor.png");
}

void drawHUD(SDL_Surface* screen, Game* game, vec2i* cursor, uint8_t cursorMode)
{
    //Background
    boxRGBA(screen, 0, 12 * 16, 240, 240, 160, 82, 40, 255);

    //Game stats
    char buffer[64];
    sprintf(buffer, "%s:%d", game->waveActive ? "Wave" : "Next", game->wave);
    stringRGBA(screen, 4, 12 * 16 + 4, buffer, 255, 255, 255, 255);
    sprintf(buffer, "%d$", game->money);
    stringRGBA(screen, 4, 12 * 16 + 4 + 8, buffer, 255, 255, 255, 255);
    sprintf(buffer, "%d <3", game->lives);
    stringRGBA(screen, 4, 12 * 16 + 4 + 16, buffer, 255, 255, 255, 255);

    //Tower buying
    //TODO: replace 64 with constant
    vec2i towerPos = (vec2i) {64, 12 * 16 + 4};
    for(uint8_t i = 0; i < NUM_TOWER_TYPES; i++)
    {
        if(towerPos.x > 64 + (16 + 4) * HUD_BUY_TOWERS_PER_LINE)
        {
            towerPos.x = 64;
            towerPos.y += 16 + 4;
        }
        drawTower(screen, i, towerPos);
        towerPos.x += 16 + 4;  //TODO: replace 16 with tower size constant
    }

    //Tower info
    rectangleRGBA(screen, 144, 12 * 16 + 1, 240 - 2, 240 - 2, 0, 0, 0, 255);
    if(cursorMode == CURSOR_HUD)
    {
        TowerType selectedTower = cursor->x + cursor->y * HUD_BUY_TOWERS_PER_LINE;
        stringRGBA(screen, 144 + 2, 12 * 16 + 3, towerTypeData[selectedTower].name, 255, 255, 255, 255);
        sprintf(buffer, "%d$", towerTypeData[selectedTower].cost);
        //TODO: color yellow if the player can't afford it
        stringRGBA(screen, 144 + 2, 12 * 16 + 3 + 8, buffer, 255, 255, 255, 255);
    }

}

//TODO: split into HUD and map cursor
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
        //TODO: 20 is 16 (tower size) + 4 (spacing), move into constatn
        SDL_Rect pos = {.x = 64 + 20 * cursor->x, .y = 4 + 12 * 16 + cursor->y * 20};
        SDL_BlitSurface(cursorTile, NULL, screen, &pos);
    }
}