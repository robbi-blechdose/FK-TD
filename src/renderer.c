#include "renderer.h"

/**
 * Macro for centering text
 * X is the length of the text
 * Note: X * 8 / 2 = X * 4
 **/
#define CENTER(X) (240 / 2 - (X) * 4)

SDL_Surface* titleScreen;
SDL_Surface* loseScreen;

SDL_Surface* cursorTile;

uint8_t animCounter;

//TODO: replace with automatic layout
HUDElement hudElements[NUM_TOWER_TYPES] = {
    {.tower = 0, .position = {.x = 0, .y = 12 * 16}, .name = "Zap"},
    {.tower = 1, .position = {.x = 48, .y = 12 * 16}, .name = "Ice"},
    {.tower = 2, .position = {.x = 96, .y = 12 * 16}, .name = "Fire"},
    {.tower = 3, .position = {.x = 96 + 56, .y = 12 * 16}, .name = "Cannon"}
};

void initRenderer()
{
    IMG_Init(IMG_INIT_PNG);
    animCounter = 0;

    //Load cursor
    cursorTile = loadPNG("res/Cursor.png");
    //Load font
    gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);

    //Load screens
    titleScreen = loadPNG("res/screens/title_screen.png");
    loseScreen = loadPNG("res/screens/game_over.png");
}

void drawMenu(SDL_Surface* screen)
{
    static uint8_t menuTimer;
    menuTimer += 4; //Uses overflow behavior to roll over

    SDL_Rect pos = {.x = 0, .y = 0};
    SDL_BlitSurface(titleScreen, NULL, screen, &pos);
    if(menuTimer < 128)
    {
        stringRGBA(screen, CENTER(11), 148, "PRESS START", 255, 255, 255, 255);
    }
    stringRGBA(screen, CENTER(8), 200, "2021 - 2024", 255, 255, 255, 255);
    stringRGBA(screen, CENTER(15), 208, "Robbi Blechdose", 255, 255, 0, 255);
    stringRGBA(screen, CENTER(7), 216, "V13Loca", 255, 0, 255, 255);
    stringRGBA(screen, CENTER(9), 224, "bickman14", 192, 0, 255, 255);
}

void drawLoseScreen(SDL_Surface* screen)
{
    SDL_Rect pos = {.x = 0, .y = 0};
    SDL_BlitSurface(loseScreen, NULL, screen, &pos);
}

void drawMapSelect(SDL_Surface* screen)
{
    static uint8_t menuTimer;
    menuTimer += 4; //Uses overflow behavior to roll over
    
    boxRGBA(screen, 0, 12 * 16, 240, 240, 160, 82, 40, 255);
    if(menuTimer < 128)
    {
        stringRGBA(screen, CENTER(18), 212, "<   SELECT MAP   >", 255, 255, 255, 255);
    }
}

//TODO
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

//TODO
void drawCursor(SDL_Surface* screen, vec2i* cursor, uint8_t cursorMode, uint8_t selectedTower)
{
    if(cursorMode == CURSOR_MAP)
    {
        SDL_Rect pos = {.x = cursor->x * 16, .y = cursor->y * 16};
        if(selectedTower != TT_NONE)
        {
            SDL_Rect rect = {.x = 0, .y = 0, .w = 16, .h = 16};
            //SDL_BlitSurface(towerTiles[selectedTower], &rect, screen, &pos);
            //circleRGBA(screen, cursor->x * 16 + 8, cursor->y * 16 + 8, towerTypes[selectedTower].radius * 16, 255, 255, 255, 255);
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