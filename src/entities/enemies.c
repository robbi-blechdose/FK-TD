#include "enemies.h"

#include <math.h>

#include "../utils.h"

//In pixels
#define ENEMY_TEXTURE_SIZE 14

const EnemyTypeData enemyTypeData[NUM_ENEMY_TYPES] = {
    [ENT_RED] =    {.containedType = ENT_NONE,   .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_0.png"},
    [ENT_BLUE] =   {.containedType = ENT_RED,    .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_1.png"},
    [ENT_GREEN] =  {.containedType = ENT_BLUE,   .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_2.png"},
    [ENT_YELLOW] = {.containedType = ENT_GREEN,  .health = 1, .speed = 1.0f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_3.png"},
    [ENT_VIOLET] = {.containedType = ENT_YELLOW, .health = 1, .speed = 1.0f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_4.png"},
    [ENT_SHIP] =   {.containedType = ENT_VIOLET, .health = 2, .speed = 1.5f / 16, .moneyValue = 2, .texturePath = "res/enemies/Enemy_5.png"}
};

SDL_Surface* enemyTextures[NUM_ENEMY_TYPES];

void initEnemies()
{
    for(uint8_t i = 0; i < NUM_ENEMY_TYPES; i++)
    {
        enemyTextures[i] = loadPNG(enemyTypeData[i].texturePath);
    }
}

void quitEnemies()
{
    //TODO: unload stuff etc.
}

void drawEnemy(SDL_Surface* screen, Enemy* enemy, int animCounter)
{
    SDL_Rect rect = {.x = (animCounter / 8 % 2) * ENEMY_TEXTURE_SIZE,
                        .y = 0,
                        .w = ENEMY_TEXTURE_SIZE, .h = ENEMY_TEXTURE_SIZE};
    //TODO: replace 16 with map tile size
    //TODO: remove magic constant 1 caused by difference between enemy and map tile size
    SDL_Rect pos = {.x = enemy->position.x * 16 + 1,
                    .y = enemy->position.y * 16 + 1};
    SDL_BlitSurface(enemyTextures[enemy->type], &rect, screen, &pos);
    //TODO: apply texture on top or tint for stat effects
}

void drawEnemies(SDL_Surface* screen, Enemy* enemies, uint16_t maxEnemies)
{
    static uint8_t animCounter = 0;
    animCounter++;

    for(uint16_t i = 0; i < maxEnemies; i++)
    {
        if(enemies[i].type != ENT_NONE)
        {
            drawEnemy(screen, &enemies[i], animCounter);
        }
    }
}

void updateEnemy(Enemy* enemy, Map* map, Game* game)
{
    vec2i tilePosition = {.x = roundf(enemy->position.x), .y = roundf(enemy->position.y)};

    //TODO: move this (the effect of reaching the end tile) somewhere else?
    if(enemy->toMove <= 0 && map->endPosition.x == tilePosition.x && map->endPosition.y == tilePosition.y)
    {
        //TODO: apply health from nested enemies...
        game->lives -= enemy->health;
        enemy->type = ENT_NONE;
    }
    
    if(enemy->toMove > 0)
    {
        float speed = enemyTypeData[enemy->type].speed;
        if(enemy->statModifiers & STAT_ICED || enemy->statModifiers & STAT_GLUED)
        {
            speed *= 0.7f; //TODO: replace magic value with defined constant
        }

        //Make sure we don't overshoot
        if(speed > enemy->toMove)
        {
            speed = enemy->toMove;
        }
        
        enemy->toMove -= speed;
        switch(enemy->direction)
        {
            case 0:
            {
                enemy->position.y -= speed;
                break;
            }
            case 1:
            {
                enemy->position.y += speed;
                break;
            }
            case 2:
            {
                enemy->position.x -= speed;
                break;
            }
            case 3:
            {
                enemy->position.x += speed;
                break;
            }
        }
    }
    else
    {
        //Direction handling
        enemy->direction = getTileAtPos(map, tilePosition.x, tilePosition.y) - 2; //TODO: remove magic number here
        enemy->toMove = 1;
    }
    
}

bool updateEnemies(Enemy* enemies, uint16_t maxEnemies, Map* map, Game* game)
{
    bool hasEnemies = false;

    for(uint16_t i = 0; i < maxEnemies; i++)
    {
        if(enemies[i].type == ENT_NONE)
        {
            continue;
        }

        hasEnemies = true;

        updateEnemy(&enemies[i], map, game);
    }

    return hasEnemies;
}

bool addEnemy(Enemy* enemies, uint16_t maxEnemies, uint8_t x, uint8_t y, uint8_t dir, uint8_t type)
{
    for(uint16_t i = 0; i < maxEnemies; i++)
    {
        if(enemies[i].type == ENT_NONE)
        {
            //We found a free spot, insert the enemy
            enemies[i].type = type;
            enemies[i].position.x = x;
            enemies[i].position.y = y;
            enemies[i].direction = dir;
            enemies[i].toMove = 0;
            enemies[i].health = enemyTypeData[type].health;
            enemies[i].statModifiers = 0;
            return true;
        }
    }
    return false;
}

void statChangeEnemy(Enemy* enemy, uint8_t stats)
{
    enemy->statModifiers ^= stats;
}

void damageEnemy(Enemy* enemy, uint16_t damage, uint16_t* money)
{

    if(enemy->health > damage)
    {
        enemy->health -= damage;
        return;
    }

    (*money) += enemyTypeData[enemy->type].moneyValue;

    if(enemyTypeData[enemy->type].containedType == ENT_NONE)
    {
        //This is the "smallest" enemy and health is <= damage
        enemy->type = ENT_NONE;
        return;
    }
    
    //We have "contained" enemies
    //Subtract damage
    damage -= enemy->health;
    //Replace enemy with "contained" enemy
    enemy->type = enemyTypeData[enemy->type].containedType;
    enemy->health = enemyTypeData[enemy->type].health;
    //If there's still damage left, apply it to the new enemy
    if(damage > 0)
    {
        damageEnemy(enemy, damage, money);
    }
}