#include "renderer.h"

//TODO: Draw projectiles

SDL_Surface* titleScreen;
SDL_Surface* loseScreen;

SDL_Surface* cursorTile;

uint8_t animCounter;
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
    {.path = "res/tiles/R_RU.png", .frames = 0}
};

#define HUD_X_LENGTH 3

HUDElement hudElements[NUM_TOWER_TYPES] = {
    {.tower = &towerTypes[0], .position = {.x = 0, .y = 12 * 16}, .name = "Zap"},
    {.tower = &towerTypes[1], .position = {.x = 48, .y = 12 * 16}, .name = "Ice"},
    {.tower = &towerTypes[2], .position = {.x = 96, .y = 12 * 16}, .name = "Fire"}
};

void initRenderer(SDL_Surface* screen)
{
    IMG_Init(IMG_INIT_PNG);
    animCounter = 0;

    uint8_t i;
    //Load cursor
    cursorTile = loadPNG("res/Cursor.png");
    //Load tiles
    for(i = 0; i < NUM_RENDER_TILES; i++)
    {
        renderTiles[i].tile = loadPNG(renderTiles[i].path);
    }
    //Load towers
    for(i = 0; i < NUM_TOWER_TYPES; i++)
    {
        towerTypes[i].tile = loadPNG(towerTypes[i].tilePath);
    }
    //Load enemies
    for(i = 0; i < NUM_ENEMY_TYPES; i++)
    {
        enemyTypes[i].tile = loadPNG(enemyTypes[i].tilePath);
    }
    //Load font
    gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);

    //Load screens
    titleScreen = loadPNG("res/screens/title_screen.png");
    loseScreen = loadPNG("res/screens/lose_screen.png");
}

void drawMenu(SDL_Surface* screen)
{
    static uint8_t menuTimer;
    menuTimer += 4; //Uses overflow behavior to roll over

    SDL_Rect pos = {.x = 0, .y = 0};
    SDL_BlitSurface(titleScreen, NULL, screen, &pos);
    if(menuTimer < 128)
    {
        stringRGBA(screen, 120 - (11 * 8) / 2, 148, "PRESS START", 255, 255, 255, 255);
    }
    stringRGBA(screen, 120 - (8 * 8) / 2, 200, "Made by:", 255, 255, 255, 255);
    stringRGBA(screen, 120 - (15 * 8) / 2, 208, "Robbi Blechdose", 255, 255, 0, 255);
    stringRGBA(screen, 120 - (7 * 8) / 2, 216, "V13Loca", 255, 0, 255, 255);
}

void drawLoseScreen(SDL_Surface* screen)
{
    SDL_Rect pos = {.x = 0, .y = 0};
    SDL_BlitSurface(loseScreen, NULL, screen, &pos);
}

void drawMap(SDL_Surface* screen, Map* map)
{
    uint8_t i, j;

    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 12; j++)
        {
            SDL_Rect pos = {.x = i * 16, .y = j * 16};
            uint8_t index = map->displayTiles[i + j * 15];
            if(renderTiles[index].frames)
            {
                SDL_Rect rect = {.x = (animCounter / 16 % renderTiles[index].frames) * 16, .y = 0, .w = 16, .h = 16};
                SDL_BlitSurface(renderTiles[index].tile, &rect, screen, &pos);
            }
            else
            {
                SDL_BlitSurface(renderTiles[index].tile, NULL, screen, &pos);
            }
        }
    }

    animCounter++;
}

void drawTowers(SDL_Surface* screen, Tower towers[])
{
    uint8_t i;
    for(i = 0; i < 225; i++)
    {
        if(towers[i].type)
        {
            SDL_Rect pos = {.x = towers[i].position.x * 16, .y = towers[i].position.y * 16};
            if(towers[i].type->frames)
            {
                SDL_Rect rect = {.x = (animCounter / 16 % towers[i].type->frames) * 16, .y = 0, .w = 16, .h = 16};
                SDL_BlitSurface(towers[i].type->tile, &rect, screen, &pos);
            }
            else
            {
                SDL_BlitSurface(towers[i].type->tile, NULL, screen, &pos);
            }
        }
    }
}

void drawEnemies(SDL_Surface* screen, Enemy enemies[])
{
    uint8_t i;
    for(i = 0; i < 225; i++)
    {
        if(enemies[i].type)
        {
            SDL_Rect pos = {.x = enemies[i].position.x, .y = enemies[i].position.y};
            SDL_BlitSurface(enemies[i].type->tile, NULL, screen, &pos);
        }
    }
}

void drawHUD(SDL_Surface* screen, Game* game)
{
    boxRGBA(screen, 0, 12 * 16, 240, 240, 160, 82, 40, 255);

    uint8_t i;
    char buffer[64];

    for(i = 0; i < NUM_TOWER_TYPES; i++)
    {
        SDL_Rect rect = {.x = 0, .y = 0, .w = 16, .h = 16};
        SDL_BlitSurface(hudElements[i].tower->tile, &rect, screen, &hudElements[i].position);
        stringRGBA(screen, hudElements[i].position.x + 16, hudElements[i].position.y,
            hudElements[i].name, 255, 255, 255, 255);
        sprintf(buffer, "%d$", hudElements[i].tower->cost);
        stringRGBA(screen, hudElements[i].position.x + 16, hudElements[i].position.y + 8,
            buffer, 255, 255, 255, 255);
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

void drawCursor(SDL_Surface* screen, Point* cursor, uint8_t cursorMode, TowerType* selectedTower)
{
    if(cursorMode == CURSOR_MAP)
    {
        SDL_Rect pos = {.x = cursor->x * 16, .y = cursor->y * 16};
        if(selectedTower)
        {
            SDL_Rect rect = {.x = 0, .y = 0, .w = 16, .h = 16};
            SDL_BlitSurface(selectedTower->tile, &rect, screen, &pos);
            circleRGBA(screen, cursor->x * 16 + 8, cursor->y * 16 + 8, selectedTower->radius * 16, 255, 255, 255, 255);
        }
        SDL_BlitSurface(cursorTile, NULL, screen, &pos);
    }
    else
    {
        uint8_t index = cursor->x + cursor->y * HUD_X_LENGTH;
        SDL_Rect pos = {.x = hudElements[index].position.x, .y = hudElements[index].position.y};
        SDL_BlitSurface(cursorTile, NULL, screen, &pos);
    }
}

TowerType* getSelectedTower(Point* cursor)
{
    uint8_t index = cursor->x + cursor->y * HUD_X_LENGTH;
    return hudElements[index].tower;
}