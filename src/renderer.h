#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include "entities.h"
#include "utils.h"
#include "map.h"

void initRenderer(SDL_Surface* screen);
void drawMap(SDL_Surface* screen, Map* map);
void drawTowers(SDL_Surface* screen, Tower towers[]);
void drawEnemies(SDL_Surface* screen, Enemy enemies[]);
void drawCursor(SDL_Surface* screen, Point* cursor);

#endif