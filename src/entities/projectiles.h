#ifndef PROJECTILES_H
#define PROJECTILES_H

#include <stdint.h>

#include "enemies.h"
#include "../effects.h"

typedef enum {
    PT_FIREBALL,
    PT_CANNONBALL,
    NUM_PROJECTILE_TYPES,
    PT_NONE
} ProjectileType;

typedef struct {
    char* tilePath;
    uint8_t frames;
    uint8_t life;
    uint8_t damage;
    uint8_t radius;
    EffectType hitEffect;
} ProjectileTypeData;

typedef struct {
    uint8_t type;
    uint8_t timer;
    vec2 position;
    vec2 source;
    vec2 target;
} Projectile;

void initProjectiles();
void quitProjectiles();

void drawProjectiles(SDL_Surface* screen, Projectile projectiles[]);

bool addProjectile(Projectile projectiles[], uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, uint8_t type);
bool updateProjectiles(Projectile projectiles[], Enemy enemies[], uint16_t* money);

#endif