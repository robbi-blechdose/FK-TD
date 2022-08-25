#include <stdlib.h>
#include <SDL.h>
#include <SDL_framerate.h>

#include "engine/input.h"

#include "renderer.h"
#include "entities.h"
#include "utils.h"
#include "wavegenerator.h"
#include "effects.h"

uint8_t running = 1;
SDL_Event event;

SDL_Surface* screen;
FPSmanager fpsManager;

#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_LOST 2
#define STATE_MAPSELECT 3
uint8_t state;

uint8_t mapSelectIndex;

//Main game fields
//TODO: Reduce this number?
#define MAX_TOWERS 225 //225 is the total number of 16x16 tiles that can be on screen at any time
#define MAX_ENEMIES 225
#define MAX_PROJECTILES 255
Tower towers[MAX_TOWERS];
Enemy enemies[MAX_ENEMIES];
Projectile projectiles[MAX_PROJECTILES];
Map* map;
Game game;

uint8_t cursorMode;
Point cursorBackup;
Point cursor;
uint8_t selectedTower;

void startGame()
{
    game.wave = 0;
    game.waveActive = 0;
    game.money = 100;
    game.lives = 25;
    //Clear tower, enemy and projectile lists
    for(uint8_t i = 0; i < MAX_TOWERS; i++)
    {
        towers[i].type = TOWER_TYPE_NONE;
    }
    for(uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].type = ENEMY_TYPE_NONE;
    }
    for(uint8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        projectiles[i].type = PROJECTILE_TYPE_NONE;
    }
    //Initialize cursors
    cursorMode = CURSOR_MAP;
    cursor.x = 0;
    cursor.y = 0;
    cursorBackup.x = 0;
    cursorBackup.y = 0;
    selectedTower = TOWER_TYPE_NONE;
}

void startWave()
{
    game.wave++;
    game.waveActive = 1;
    initWaveGenerator(game.wave, getStartPos(map));
}

void calcFrame()
{
    switch(state)
    {
        case STATE_MENU:
        {
            if(keyUp(B_START))
            {
                state = STATE_MAPSELECT;
            }
            break;
        }
        case STATE_GAME:
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
                if(cursorMode == CURSOR_MAP && selectedTower != TOWER_TYPE_NONE)
                {
                    if(game.money >= towerTypes[selectedTower].cost && placeTower(&cursor, towers, selectedTower, map))
                    {
                        game.money -= towerTypes[selectedTower].cost;
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
                    selectedTower = TOWER_TYPE_NONE;
                }
            }
            else if(keyUp(B_SELECT))
            {
                //Swap cursors
                Point temp;
                copyPoint(&temp, &cursor);
                copyPoint(&cursor, &cursorBackup);
                copyPoint(&cursorBackup, &temp);

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
                updateTowers(towers, enemies, projectiles, &game.money);
                uint8_t hasEnemies = updateEnemies(enemies, map, &game);
                uint8_t hasWave = updateWaveGenerator(enemies, game.wave);
                uint8_t hasProjectiles = updateProjectiles(projectiles, enemies, &game.money);
                game.waveActive = hasEnemies || hasWave || hasProjectiles;
            }

            if(!game.lives)
            {
                state = STATE_LOST;
            }

            break;
        }
        case STATE_LOST:
        {
            if(keyUp(B_START))
            {
                state = STATE_MENU;
            }
            break;
        }
        case STATE_MAPSELECT:
        {
            if(keyUp(B_START))
            {
                state = STATE_GAME;
                map = &maps[mapSelectIndex];
                startGame();
            }
            else if(keyUp(B_LEFT))
            {
                if(mapSelectIndex > 0)
                {
                    mapSelectIndex--;
                }
                break;
            }
            else if(keyUp(B_RIGHT))
            {
                if(mapSelectIndex < NUM_MAPS - 1)
                {
                    mapSelectIndex++;
                }
            }
            break;
        }
    }
}

void drawFrame()
{
    switch(state)
    {
        case STATE_MENU:
        {
            drawMenu(screen);
            break;
        }
        case STATE_GAME:
        {
            //Draw
            drawMap(screen, map);
            drawTowers(screen, towers);
            drawEnemies(screen, enemies);
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

    state = STATE_MENU;
    mapSelectIndex = 0;
    initRenderer();
    initEffects();

    //Main loop
    while(running)
    {
        running = handleInput();
        
        calcFrame();
        drawFrame();

        SDL_framerateDelay(&fpsManager);
    }

    SDL_Quit();
	return 0;
}