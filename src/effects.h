#ifndef _EFFECTS_H
#define _EFFECTS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "utils.h"

typedef enum {
    E_NONE,
    E_ZAP,
    E_ICE,
    E_EXPLOSION
} EffectType;

typedef struct {
    EffectType type;
    Point a, b, middle;
    uint8_t radius;
    uint8_t timer;
} Effect;

void initEffects();
void addEffect(EffectType t, Point* tower, Point* enemy, uint8_t radius);
void drawEffects(SDL_Surface* screen);

#endif