#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"
#include "map.h"
#include "effects.h"

typedef enum {
    A_NONE,
    A_ZAP,
    A_ICE,
    A_FIRE,
    A_CANNON
} AttackType;

typedef struct {
    AttackType attack;
    uint16_t cooldown;
    uint16_t damage;
    uint8_t radius;

    uint16_t cost;

    char* tilePath;
    uint8_t frames;
} TowerType;

typedef struct {
    uint8_t type;
    Point position;
    uint16_t cooldown;
} Tower;

typedef struct EnemyType EnemyType;
struct EnemyType {
    uint16_t health;
    float speed;
    uint8_t contains;

    char* tilePath;
};

typedef struct {
    uint8_t type;
    Point position;
    uint8_t direction;
    float toMove;
    float posDiff;
    uint16_t health;
    uint8_t isIced;
} Enemy;

typedef struct {
    char* tilePath;
    uint8_t frames;
    uint8_t life;
    uint8_t damage;
    uint8_t radius;
    EffectType hitEffect;
} ProjectileType;

typedef struct {
    uint8_t type;
    uint8_t timer;
    Point position;
    Point source;
    Point target;
} Projectile;

#define NUM_TOWER_TYPES 4
#define TOWER_TYPE_NONE 255
extern const TowerType towerTypes[NUM_TOWER_TYPES];
extern SDL_Surface* towerTiles[NUM_TOWER_TYPES];

#define NUM_ENEMY_TYPES 6
#define ENEMY_TYPE_NONE 255
extern const EnemyType enemyTypes[NUM_ENEMY_TYPES];
extern SDL_Surface* enemyTiles[NUM_ENEMY_TYPES];

#define NUM_PROJECTILE_TYPES 2
#define PROJECTILE_TYPE_NONE 255
extern const ProjectileType projectileTypes[NUM_PROJECTILE_TYPES];
extern SDL_Surface* projectileTiles[NUM_PROJECTILE_TYPES];

bool placeTower(Point* cursor, Tower towers[], uint8_t type, Map* map);
bool addEnemy(Enemy enemies[], uint8_t x, uint8_t y, uint8_t dir, uint8_t type);
bool addProjectile(Projectile projectiles[], uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, uint8_t type);

void updateTowers(Tower towers[], Enemy enemies[], Projectile projectiles[], uint16_t* money);
bool updateEnemies(Enemy enemies[], Map* map, Game* game);
bool updateProjectiles(Projectile projectiles[], Enemy enemies[], uint16_t* money);

#endif