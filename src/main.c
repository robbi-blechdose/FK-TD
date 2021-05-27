#include <SDL.h>
#include <SDL_framerate.h>

#include "renderer.h"
#include "entities.h"
#include "utils.h"

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

uint16_t money;
TowerType* selectedTower;

Point cursor;

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
                    cursor.y -= 16;
                }
                break;
            }
            case SDLK_d:
            {
                if(cursor.y < 176)
                {
                    cursor.y += 16;
                }
                break;
            }
            case SDLK_l:
            {
                if(cursor.x > 0)
                {
                    cursor.x -= 16;
                }
                break;
            }
            case SDLK_r:
            {
                if(cursor.x < 224)
                {
                    cursor.x += 16;
                }
                break;
            }
            case SDLK_a:
            {
                //if we have a tower selected
                if(selectedTower)
                {
                    if(money >= selectedTower->cost && placeTower(&cursor, towers, selectedTower))
                    {
                        money -= selectedTower->cost;
                        selectedTower = 0;
                        //TODO: Play "placed" sound
                    }
                    else
                    {
                        //TODO: Play "not placed" sound
                    }
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

    //Init game
    initRenderer(screen);
    money = 100;

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

        //Update
        updateTowers(towers);
        updateEnemies(enemies);

        //Draw
        drawMap(screen, &maps[0]);
        drawTowers(screen, towers);
        //TODO: Enemies
        drawCursor(screen, &cursor);
        SDL_Flip(screen);
        SDL_framerateDelay(&fpsManager);
    }

    SDL_Quit();
	return 0;
}