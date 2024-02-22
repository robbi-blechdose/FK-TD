#ifndef TOWERS_H
#define TOWERS_H

#include <stdint.h>
#include <SDL.h>

#include "../engine/math.h"

#include "../map.h"
#include "enemies.h"
#include "projectiles.h"

//TODO: do we need this? seems redundant
typedef enum {
    A_NONE,
    A_ZAP,
    A_ICE,
    A_FIRE,
    A_CANNON
} AttackType;

typedef enum {
    TT_ZAP,
    TT_ICE,
    TT_FIREBALL,
    TT_CANNON,
    NUM_TOWER_TYPES,
    TT_NONE
} TowerType;

typedef struct {
    const char* name;

    char* texturePath;
    uint8_t numFrames;

    //TODO: do we need this? seems redundant
    AttackType attack;
    uint16_t cooldown;
    uint16_t damage;
    uint8_t radius;

    uint16_t cost;
} TowerTypeData;

typedef struct {
    TowerType type;
    vec2i position;
    uint16_t cooldown;
} Tower;

void initTowers();
void quitTowers();

void drawTowers(SDL_Surface* screen, Tower* towers, uint16_t maxTowers);
void drawTowerWithRange(SDL_Surface* screen, TowerType tower, vec2i position);

bool placeTower(vec2i* cursor, Tower* towers, uint16_t maxTowers, uint8_t type, Map* map);
void updateTowers(Tower* towers, uint16_t maxTowers, Enemy* enemies, uint16_t maxEnemies, Projectile projectiles[], uint16_t* money);

#endif