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
    ProjectileType type;
    uint8_t timer;
    vec2 position;
    vec2 source;
    vec2 target;
} Projectile;

void initProjectiles();
void quitProjectiles();

void drawProjectiles(SDL_Surface* screen, Projectile* projectiles, uint16_t maxProjectiles);

bool addProjectile(Projectile* projectiles, uint16_t maxProjectiles, vec2 sourcePos, vec2 targetPos, ProjectileType type);
bool updateProjectiles(Projectile* projectiles, uint16_t maxProjectiles, Enemy* enemies, uint16_t maxEnemies, uint16_t* money);

#endif