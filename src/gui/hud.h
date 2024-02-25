#ifndef HUD_H
#define HUD_H

#include <stdint.h>
#include <SDL.h>

#include "../engine/math.h"
#include "../entities/towers.h"

#define CURSOR_MAP 0
#define CURSOR_HUD 1

void initHUD();

void drawHUD(SDL_Surface* screen, Game* game, vec2i* cursor, uint8_t cursorMode);
void drawCursor(SDL_Surface* screen, vec2i* cursors, uint8_t cursorMode, TowerType selectedTower);

#endif