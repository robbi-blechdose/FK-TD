#ifndef HUD_H
#define HUD_H

#include <stdint.h>
#include <SDL.h>

#include "../engine/math.h"
#include "../entities/towers.h"

typedef struct {
    TowerType tower;
    SDL_Rect position;
    char* name;
} HUDElement;

#define CURSOR_MAP 0
#define CURSOR_HUD 1

void initHUD();

void drawHUD(SDL_Surface* screen, Game* game);
void drawCursor(SDL_Surface* screen, vec2i* cursors, uint8_t cursorMode, TowerType selectedTower);

#endif