#include "enemies.h"

#include <math.h>

#include "../utils.h"

const EnemyTypeData enemyTypeData[NUM_ENEMY_TYPES] = {
    [ENT_RED] =    {.containedType = ENT_NONE,   .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_0.png", .textureFrameSize = 16},
    [ENT_BLUE] =   {.containedType = ENT_RED,    .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_1.png", .textureFrameSize = 16},
    [ENT_GREEN] =  {.containedType = ENT_BLUE,   .health = 1, .speed = 0.8f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_2.png", .textureFrameSize = 16},
    [ENT_YELLOW] = {.containedType = ENT_GREEN,  .health = 1, .speed = 1.0f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_3.png", .textureFrameSize = 16},
    [ENT_VIOLET] = {.containedType = ENT_YELLOW, .health = 1, .speed = 1.0f / 16, .moneyValue = 1, .texturePath = "res/enemies/Enemy_4.png", .textureFrameSize = 16},
    [ENT_SHIP] =   {.containedType = ENT_VIOLET, .health = 2, .speed = 1.5f / 16, .moneyValue = 2, .texturePath = "res/enemies/Enemy_5.png", .textureFrameSize = 16}
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
    uint8_t textureFrameSize = enemyTypeData[enemy->type].textureFrameSize;
    SDL_Rect rect = {.x = (animCounter / 8 % 2) * textureFrameSize,
                        .y = 0,
                        .w = textureFrameSize,
                        .h = textureFrameSize};
    //TODO: replace 16 with map tile size
    SDL_Rect pos = {.x = enemy->position.x * 16,
                    .y = enemy->position.y * 16};
    SDL_BlitSurface(enemyTextures[enemy->type], &rect, screen, &pos);
    if(enemy->statModifiers & STAT_ICED)
    {
        rect.y = 16;
        SDL_BlitSurface(enemyTextures[enemy->type], &rect, screen, &pos);
    }
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

void updateEnemy(Enemy* enemy, const Map* map, Game* game)
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
        if(enemy->statModifiers & STAT_ICED)
        {
            speed *= 0.7f; //TODO: replace magic value with defined constant
        }
        if(enemy->statModifiers & STAT_STUNNED)
        {
            speed = 0;
            enemy->stunTimer--;
        }

        //Make sure we don't overshoot
        if(speed > enemy->toMove)
        {
            speed = enemy->toMove;
        }
        
        enemy->toMove -= speed;
        enemy->totalDistance += speed;
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

bool updateEnemies(Enemy* enemies, uint16_t maxEnemies, const Map* map, Game* game)
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
            enemies[i].totalDistance = 0;
            enemies[i].health = enemyTypeData[type].health;
            enemies[i].statModifiers = 0;
            return true;
        }
    }
    return false;
}

void addStatToEnemy(Enemy* enemy, uint8_t stats)
{
    enemy->statModifiers |= stats;
    if(stats & STAT_STUNNED)
    {
        enemy->stunTimer = 10; //TODO: replace magic number with defined constant
    }
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