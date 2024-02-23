#include "menus.h"

#include <stdint.h>
#include <SDL_gfxPrimitives.h>

#include "../utils.h"
#include "../version.h"

SDL_Surface* titleScreen;
SDL_Surface* loseScreen;

void initMenus()
{
    titleScreen = loadPNG("res/screens/title_screen.png");
    loseScreen = loadPNG("res/screens/game_over.png");
}

void quitMenus()
{
    //TODO
}

void drawMenu(SDL_Surface* screen)
{
    static uint8_t menuTimer;
    menuTimer += 4; //Uses overflow behavior to roll over

    SDL_Rect pos = {.x = 0, .y = 0};
    SDL_BlitSurface(titleScreen, NULL, screen, &pos);
    stringRGBA(screen, CENTER(strlen(GAME_VERSION)), 132, GAME_VERSION, 255, 255, 255, 255);
    if(menuTimer < 128)
    {
        stringRGBA(screen, CENTER(11), 156, "PRESS START", 255, 255, 255, 255);
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