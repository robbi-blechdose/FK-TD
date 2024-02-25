#ifndef TOWERS_H
#define TOWERS_H

#include <stdint.h>
#include <SDL.h>

#include "../engine/math.h"

#include "../map.h"
#include "enemies.h"
#include "projectiles.h"

typedef enum {
    TT_ZAP,
    TT_ICE,
    TT_FIREBALL,
    TT_CANNON,
    NUM_TOWER_TYPES,
    TT_NONE
} TowerType;

//TODO: add possibility for "firing" and "ready" frames along with idle frames

typedef struct {
    const char* name;

    char* texturePath;
    uint8_t numFrames;

    uint16_t cooldown;
    uint16_t damage;
    float radius;

    uint16_t cost;
} TowerTypeData;

typedef struct {
    TowerType type;
    vec2i position;
    uint16_t cooldown;
} Tower;

extern const TowerTypeData towerTypeData[NUM_TOWER_TYPES];

void initTowers();
void quitTowers();

void drawTower(SDL_Surface* screen, TowerType tower, vec2i position);
void drawTowerWithRange(SDL_Surface* screen, TowerType tower, vec2i position);
void drawTowers(SDL_Surface* screen, Tower* towers, uint16_t maxTowers);

bool placeTower(vec2i* cursor, Tower* towers, uint16_t maxTowers, uint8_t type, const Map* map);
void updateTowers(Tower* towers, uint16_t maxTowers, Enemy* enemies, uint16_t maxEnemies, Projectile* projectiles, uint16_t maxProjectiles, uint16_t* money);

#endif