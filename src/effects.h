#ifndef _EFFECTS_H
#define _EFFECTS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "utils.h"

typedef enum {
    NONE,
    ZAP
} EffectType;

typedef struct {
    EffectType type;
    Point a, b, middle;
    uint8_t timer;
} Effect;

void addEffect(EffectType t, Point* a, Point* b);
void drawEffects(SDL_Surface* screen);

#endif