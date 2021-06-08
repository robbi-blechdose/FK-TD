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

#define STATE_MENU 0
#define STATE_GAME 1
uint8_t state;

//Main game fields
//TODO: Reduce this number?
#define MAX_TOWERS 225 //225 is the total number of 16x16 tiles that can be on screen at any time
#define MAX_ENEMIES 225
Tower towers[MAX_TOWERS];
Enemy enemies[MAX_ENEMIES];

Game game;

uint8_t cursorMode;
Point cursorBackup;
Point cursor;
TowerType* selectedTower;

void startGame()
{
    game.wave = 0;
    game.waveActive = 0;
    game.money = 100;
    game.lives = 50;
    game.map = &maps[0];
}

void startWave()
{
    game.wave++;
    game.waveActive = 1;
    initWaveGenerator(game.wave);
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
                    if(game.money >= selectedTower->cost && placeTower(&cursor, towers, selectedTower, game.map))
                    {
                        game.money -= selectedTower->cost;
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
                if(!game.waveActive)
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

    state = STATE_MENU;
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

            if(state == STATE_MENU)
            {
                if(event.type == SDL_KEYUP)
                {
                    if(event.key.keysym.sym == SDLK_s)
                    {
                        state = STATE_GAME;
                        startGame();
                    }
                }
            }
            else //if(state == STATE_GAME)
            {
                handleInput();
            }
        }

        if(state == STATE_MENU)
        {
            drawMenu(screen);
        }
        else //if(state == STATE_GAME)
        {
            if(game.waveActive)
            {
                //Update
                updateTowers(towers, enemies, &game.money);
                uint8_t hasEnemies = updateEnemies(enemies, &maps[0], &game);
                uint8_t hasWave = updateWaveGenerator(enemies, game.wave);
                game.waveActive = hasEnemies || hasWave;
            }

            //Draw
            drawMap(screen, game.map);
            drawTowers(screen, towers);
            drawEnemies(screen, enemies);
            drawHUD(screen, &game);
            drawCursor(screen, &cursor, cursorMode, selectedTower);
            drawEffects(screen);
        }

        SDL_Flip(screen);
        SDL_framerateDelay(&fpsManager);
    }

    SDL_Quit();
	return 0;
}