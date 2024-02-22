#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include <SDL_framerate.h>

#include "engine/input.h"

#include "entities/enemies.h"
#include "entities/projectiles.h"
#include "entities/towers.h"

#include "gui/hud.h"
#include "gui/menus.h"
#include "utils.h"
#include "wavegenerator.h"
#include "effects.h"

bool running = true;
SDL_Event event;

SDL_Surface* screen;
FPSmanager fpsManager;

typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_LOST,
    STATE_MAPSELECT
} GameState;

GameState gameState;

uint8_t mapSelectIndex;

//Main game fields

//TODO: consider replacing the tower list with an array the size of the map?
//This would allow us to remove the position field entirely and just go by index

#define MAX_TOWERS 225 //225 is the total number of 16x16 tiles that can be on screen at any time
#define MAX_ENEMIES 1024
#define MAX_PROJECTILES 255
Tower towers[MAX_TOWERS];
Enemy enemies[MAX_ENEMIES];
Projectile projectiles[MAX_PROJECTILES];
const Map* map;
Game game;

uint8_t cursorMode;
vec2i cursorBackup;
vec2i cursor;
TowerType selectedTower;

void startGame()
{
    game.wave = 0;
    game.waveActive = 0;
    game.money = 100;
    game.lives = 25;
    //Clear tower, enemy and projectile lists
    for(uint16_t i = 0; i < MAX_TOWERS; i++)
    {
        towers[i].type = TT_NONE;
    }
    for(uint16_t i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].type = ENT_NONE;
    }
    for(uint16_t i = 0; i < MAX_PROJECTILES; i++)
    {
        projectiles[i].type = PT_NONE;
    }
    //Initialize cursors
    cursorMode = CURSOR_MAP;
    cursor.x = 0;
    cursor.y = 0;
    cursorBackup.x = 0;
    cursorBackup.y = 0;
    selectedTower = TT_NONE;
}

void startWave()
{
    game.wave++;
    game.waveActive = 1;
    initWaveGenerator(game.wave, map->startPosition);
}

void calcFrameGame()
{
    if(keyUp(B_UP))
    {
        if(cursor.y > 0)
        {
            cursor.y--;
        }
    }
    else if(keyUp(B_DOWN))
    {
        if(cursorMode == CURSOR_MAP)
        {
            if(cursor.y < 11)
            {
                cursor.y++;
            }
        }
    }
    
    if(keyUp(B_LEFT))
    {
        if(cursor.x > 0)
        {
            cursor.x--;
        }
    }
    else if(keyUp(B_RIGHT))
    {
        if(cursorMode == CURSOR_MAP)
        {
            if(cursor.x < 14)
            {
                cursor.x++;
            }
        }
        else
        {
            if(cursor.x < NUM_TOWER_TYPES - 1)
            {
                cursor.x++;
            }
        }
    }

    if(keyUp(B_A))
    {
        if(cursorMode == CURSOR_MAP && selectedTower != TT_NONE)
        {
            if(game.money >= towerTypeData[selectedTower].cost && placeTower(&cursor, towers, MAX_TOWERS, selectedTower, map))
            {
                game.money -= towerTypeData[selectedTower].cost;
                //TODO: Play "placed" sound
            }
            else
            {
                //TODO: Play "not placed" sound
            }
        }
        else
        {
            selectedTower = cursor.x + cursor.y; //TODO: Multiply y with max x
            //TODO: Play "selected" sound
        }
    }
    else if(keyUp(B_B))
    {
        if(selectedTower)
        {
            selectedTower = TT_NONE;
        }
    }
    else if(keyUp(B_SELECT))
    {
        //Swap cursors
        vec2i temp;
        vec2i_copy(&temp, &cursor);
        vec2i_copy(&cursor, &cursorBackup);
        vec2i_copy(&cursorBackup, &temp);

        if(cursorMode == CURSOR_MAP)
        {
            cursorMode = CURSOR_HUD;
        }
        else
        {
            cursorMode = CURSOR_MAP;
        }
    }
    else if(keyUp(B_START))
    {
        if(!game.waveActive)
        {
            startWave();
        }
    }

    if(game.waveActive)
    {
        //Update
        updateTowers(towers, MAX_TOWERS, enemies, MAX_ENEMIES, projectiles, &game.money);
        bool hasEnemies = updateEnemies(enemies, MAX_ENEMIES, map, &game);
        bool hasWave = updateWaveGenerator(enemies, MAX_ENEMIES, game.wave);
        bool hasProjectiles = updateProjectiles(projectiles, enemies, &game.money);
        game.waveActive = hasEnemies || hasWave || hasProjectiles;
    }

    if(!game.lives)
    {
        gameState = STATE_LOST;
    }
}

void calcFrameMapselect()
{
    if(keyUp(B_START))
    {
        gameState = STATE_GAME;
        map = &maps[mapSelectIndex];
        startGame();
    }
    else if(keyUp(B_LEFT))
    {
        if(mapSelectIndex > 0)
        {
            mapSelectIndex--;
        }
    }
    else if(keyUp(B_RIGHT))
    {
        if(mapSelectIndex < NUM_MAPS - 1)
        {
            mapSelectIndex++;
        }
    }
}

void calcFrame()
{
    switch(gameState)
    {
        case STATE_MENU:
        {
            if(keyUp(B_START))
            {
                gameState = STATE_MAPSELECT;
            }
            break;
        }
        case STATE_GAME:
        {
            calcFrameGame();
            break;
        }
        case STATE_LOST:
        {
            if(keyUp(B_START))
            {
                gameState = STATE_MENU;
            }
            break;
        }
        case STATE_MAPSELECT:
        {
            calcFrameMapselect();
            break;
        }
    }
}

void drawFrame()
{
    switch(gameState)
    {
        case STATE_MENU:
        {
            drawMenu(screen);
            break;
        }
        case STATE_GAME:
        {
            drawMap(screen, map);
            drawTowers(screen, towers, MAX_TOWERS);
            drawEnemies(screen, enemies, MAX_ENEMIES);
            drawProjectiles(screen, projectiles);
            drawHUD(screen, &game);
            drawCursor(screen, &cursor, cursorMode, selectedTower);
            drawEffects(screen);
            break;
        }
        case STATE_LOST:
        {
            drawLoseScreen(screen);
            break;
        }
        case STATE_MAPSELECT:
        {
            drawMap(screen, &maps[mapSelectIndex]);
            drawMapSelect(screen);
            break;
        }
    }

    SDL_Flip(screen);
}

int main(int argc, char **argv)
{
    //Setup SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    screen = SDL_SetVideoMode(240, 240, 16, SDL_SWSURFACE);
    SDL_ShowCursor(SDL_DISABLE);
    //Setup framerate
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 50);
    srand(time(NULL));

    gameState = STATE_MENU;
    mapSelectIndex = 0;

    initPNG();
    initFont();
    initHUD();
    initMenus();

    initEffects();

    initMap();
    initEnemies();
    initTowers();
    initProjectiles();

    //Main loop
    while(running)
    {
        running = handleInput();
        
        calcFrame();
        drawFrame();

        SDL_framerateDelay(&fpsManager);
    }

    quitMap();
    quitEnemies();
    quitTowers();
    quitProjectiles();

    SDL_Quit();
	return 0;
}