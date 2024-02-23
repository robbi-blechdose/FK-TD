#ifndef ENEMIES_H
#define ENEMIES_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#include "../engine/math.h"

#include "../map.h"
#include "../utils.h"

typedef enum {
    ENT_RED,
    ENT_BLUE,
    ENT_GREEN,
    ENT_YELLOW,
    ENT_VIOLET,
    ENT_SHIP,
    NUM_ENEMY_TYPES,
    ENT_NONE
} EnemyType;

//TODO: resistance to tower types

typedef struct {
    EnemyType containedType;
    float health;
    float speed;
    uint8_t moneyValue;

    char* texturePath;
} EnemyTypeData;

#define STAT_ICED    0b00000001
#define STAT_BURNING 0b00000010
#define STAT_GLUED   0b00000100
//TODO more stats...

typedef struct {
    EnemyType type;

    uint16_t health;
    vec2 position;
    uint8_t direction;
    float toMove;

    uint8_t statModifiers;
} Enemy;

void initEnemies();
void quitEnemies();

void drawEnemies(SDL_Surface* screen, Enemy* enemies, uint16_t maxEnemies);
bool updateEnemies(Enemy* enemies, uint16_t maxEnemies, Map* map, Game* game);

bool addEnemy(Enemy* enemies, uint16_t maxEnemies, uint8_t x, uint8_t y, uint8_t dir, uint8_t type);

void addStatToEnemy(Enemy* enemy, uint8_t stats);
void damageEnemy(Enemy* enemy, uint16_t damage, uint16_t* money);

#endif