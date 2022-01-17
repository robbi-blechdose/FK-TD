#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxPrimitives_font.h>
#include "entities.h"
#include "utils.h"
#include "map.h"

typedef struct {
    uint8_t tower;
    SDL_Rect position;
    char* name;
} HUDElement;

typedef struct {
    char* path;
    uint8_t frames;
    SDL_Surface* tile;
} RenderTile;

#define CURSOR_MAP 0
#define CURSOR_HUD 1

void initRenderer(SDL_Surface* screen);

void drawMenu(SDL_Surface* screen);
void drawLoseScreen(SDL_Surface* screen);
void drawMapSelect(SDL_Surface* screen);

void drawMap(SDL_Surface* screen, Map* map);
void drawTowers(SDL_Surface* screen, Tower towers[]);
void drawEnemies(SDL_Surface* screen, Enemy enemies[]);
void drawHUD(SDL_Surface* screen, Game* game);
void drawCursor(SDL_Surface* screen, Point* cursors, uint8_t cursorMode, uint8_t selectedTower);

#endif