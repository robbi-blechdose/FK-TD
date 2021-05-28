#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <SDL.h>
#include <stdint.h>
#include "utils.h"

typedef enum {
    NONE,
    FIRE,
    ICE,
    POISON
} Effect;

typedef struct {
    uint16_t cooldown;
    uint16_t damage;
    Effect effect;

    uint16_t cost;

    char* tilePath;
    SDL_Surface* tile;
} TowerType;

typedef struct {
    TowerType* type;

    Point position;
    uint16_t cooldown;
} Tower;

typedef struct {
    uint16_t health;
    uint16_t speed;

    char* tilePath;
    SDL_Surface* tile;
} EnemyType;

typedef struct {
    EnemyType* type;

    Point position;
    uint16_t health;
} Enemy;

#define NUM_TOWER_TYPES 2
extern TowerType towerTypes[NUM_TOWER_TYPES];

#define NUM_ENEMY_TYPES 1
extern EnemyType enemyTypes[NUM_ENEMY_TYPES];

int placeTower(Point* cursor, Tower towers[], TowerType* new);

void updateTowers(Tower towers[]);
void updateEnemies(Enemy enemies[]);

#endif