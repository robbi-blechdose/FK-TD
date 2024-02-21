#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxPrimitives_font.h>

#include "engine/math.h"

#include "utils.h"
#include "map.h"
#include "entities/towers.h"

typedef struct {
    TowerType tower;
    SDL_Rect position;
    char* name;
} HUDElement;

#define CURSOR_MAP 0
#define CURSOR_HUD 1

void initRenderer();

void drawMenu(SDL_Surface* screen);
void drawLoseScreen(SDL_Surface* screen);
void drawMapSelect(SDL_Surface* screen);

void drawHUD(SDL_Surface* screen, Game* game);
void drawCursor(SDL_Surface* screen, vec2i* cursors, uint8_t cursorMode, uint8_t selectedTower);

#endif