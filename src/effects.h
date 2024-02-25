#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "engine/math.h"

typedef enum {
    EFT_NONE,
    EFT_ZAP,
    EFT_ICE,
    EFT_EXPLOSION
} EffectType;

typedef struct {
    EffectType type;
    vec2i a, b;
    uint8_t radius;
    uint8_t timer;
} Effect;

void initEffects();
void quitEffects();

void addEffect(EffectType type, vec2 position, vec2 enemy, uint8_t radius);
void drawEffects(SDL_Surface* screen);

#endif