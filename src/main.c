#include <stdlib.h>
#include <SDL.h>
#include <SDL_framerate.h>

#include "renderer.h"
#include "entities.h"
#include "utils.h"
#include "wavegenerator.h"
#include "effects.h"

uint8_t running = 1;
SDL_Event event;

SDL_Surface* screen;
FPSmanager fpsManager;

//Main game fields
//TODO: Reduce this number?
#define MAX_TOWERS 225 //225 is the total number of 16x16 tiles that can be on screen at any time
#define MAX_ENEMIES 225
Tower towers[MAX_TOWERS];
Enemy enemies[MAX_ENEMIES];

uint16_t wave;
uint8_t waveActive;
uint16_t money;
uint8_t lives;
TowerType* selectedTower;

uint8_t cursorMode;
Point cursorBackup;
Point cursor;

void startWave()
{
    wave++;
    waveActive = 1;
    initWaveGenerator(wave);
}

void handleInput()
{
    if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_u:
            {
                if(cursor.y > 0)
                {
                    cursor.y--;
                }
                break;
            }
            case SDLK_d:
            {
                if(cursorMode == CURSOR_MAP)
                {
                    if(cursor.y < 11)
                    {
                        cursor.y++;
                    }
                }
                else
                {
                    if(cursor.y < 0)
                    {
                        cursor.y++;
                    }
                }
                break;
            }
            case SDLK_l:
            {
                if(cursor.x > 0)
                {
                    cursor.x--;
                }
                break;
            }
            case SDLK_r:
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
                    if(cursor.x < 2)
                    {
                        cursor.x++;
                    }
                }
                break;
            }
            case SDLK_a:
            {
                if(cursorMode == CURSOR_MAP && selectedTower)
                {
                    if(money >= selectedTower->cost && placeTower(&cursor, towers, selectedTower))
                    {
                        money -= selectedTower->cost;
                        //TODO: Play "placed" sound
                    }
                    else
                    {
                        //TODO: Play "not placed" sound
                    }
                }
                else
                {
                    selectedTower = getSelectedTower(&cursor);
                    //TODO: Play "selected" sound
                }
                break;
            }
            case SDLK_b:
            {
                if(selectedTower)
                {
                    selectedTower = NULL;
                }
                break;
            }
            case SDLK_k:
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
                break;
            }
            case SDLK_s:
            {
                if(!waveActive)
                {
                    startWave();
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

//TODO: Move all stuff into a main game object so we can pass that around as a pointer

int main(int argc, char **argv)
{
    //Setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(240, 240, 16, 0);
    SDL_ShowCursor(SDL_DISABLE);
    //Setup framerate
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 50);
    srand(time(NULL));

    //Init game
    wave = 0;
    waveActive = 0;
    money = 100;
    lives = 50;
    initRenderer(screen);
    initEffects();

    //Main loop
    while(running)
    {
        //Read input
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
            handleInput();
        }

        if(waveActive)
        {
            //Update
            updateTowers(towers, enemies, &money);
            uint8_t hasEnemies = updateEnemies(enemies, &maps[0], &lives, &money);
            uint8_t hasWave = updateWaveGenerator(enemies, wave);
            waveActive = hasEnemies || hasWave;
        }

        //Draw
        drawMap(screen, &maps[0]);
        drawTowers(screen, towers);
        drawEnemies(screen, enemies);
        drawHUD(screen, wave, money, lives);
        drawCursor(screen, &cursor, cursorMode, selectedTower);
        drawEffects(screen);
        SDL_Flip(screen);
        SDL_framerateDelay(&fpsManager);
    }

    SDL_Quit();
	return 0;
}