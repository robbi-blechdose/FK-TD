#ifndef MENUS_H
#define MENUS_H

#include <SDL.h>

void initMenus();
void quitMenus();

void drawMenu(SDL_Surface* screen);
void drawLoseScreen(SDL_Surface* screen);
void drawMapSelect(SDL_Surface* screen);

#endif