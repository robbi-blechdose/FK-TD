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

typedef struct {
    EnemyType containedType;
    float health;
    float speed;
    uint8_t moneyValue;

    char* tilePath;
} EnemyTypeData;

typedef struct {
    EnemyType type;

    uint16_t health;
    vec2i position;
    uint8_t direction;
    float toMove;
    float posDiff;

    //Status modifiers
    bool isIced;
} Enemy;

void initEnemies();
void quitEnemies();

void drawEnemies(SDL_Surface* screen, Enemy* enemies, uint16_t maxEnemies);

bool addEnemy(Enemy* enemies, uint16_t maxEnemies, uint8_t x, uint8_t y, uint8_t dir, uint8_t type);
void damageEnemy(Enemy* enemy, uint16_t damage, bool iced, uint16_t* money);
bool updateEnemies(Enemy* enemies, uint16_t maxEnemies, Map* map, Game* game);

#endif