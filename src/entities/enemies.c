#include "enemies.h"

#include "../utils.h"

//In pixels
#define ENEMY_TEXTURE_SIZE 14

const EnemyTypeData enemyTypeData[NUM_ENEMY_TYPES] = {
    [ENT_RED] =    {.containedType = ENT_NONE,   .health = 1, .speed = 0.8f, .moneyValue = 1, .tilePath = "res/enemies/Enemy_0.png"},
    [ENT_BLUE] =   {.containedType = ENT_RED,    .health = 1, .speed = 1.0f, .moneyValue = 1,  .tilePath = "res/enemies/Enemy_1.png"},
    [ENT_GREEN] =  {.containedType = ENT_BLUE,   .health = 1, .speed = 1.2f, .moneyValue = 1,  .tilePath = "res/enemies/Enemy_2.png"},
    [ENT_YELLOW] = {.containedType = ENT_GREEN,  .health = 1, .speed = 1.5f, .moneyValue = 1,  .tilePath = "res/enemies/Enemy_3.png"},
    [ENT_VIOLET] = {.containedType = ENT_YELLOW, .health = 1, .speed = 2.0f, .moneyValue = 1,  .tilePath = "res/enemies/Enemy_4.png"},
    [ENT_SHIP] =   {.containedType = ENT_VIOLET, .health = 2, .speed = 2.5f, .moneyValue = 2,  .tilePath = "res/enemies/Enemy_5.png"}
};

SDL_Surface* enemyTextures[NUM_ENEMY_TYPES];

void initEnemies()
{
    for(uint8_t i = 0; i < NUM_ENEMY_TYPES; i++)
    {
        enemyTextures[i] = loadPNG(enemyTypeData[i].tilePath);
    }
}

void quitEnemies()
{
    //TODO: unload stuff etc.
}

void drawEnemies(SDL_Surface* screen, Enemy* enemies, uint16_t maxEnemies)
{
    //TODO
    int animCounter = 0;

    for(uint16_t i = 0; i < maxEnemies; i++)
    {
        if(enemies[i].type != ENT_NONE)
        {
            SDL_Rect rect = {.x = (animCounter / 8 % 2) * ENEMY_TEXTURE_SIZE,
                                .y = 0,
                                .w = ENEMY_TEXTURE_SIZE, .h = ENEMY_TEXTURE_SIZE};
            SDL_Rect pos = {.x = enemies[i].position.x - ENEMY_TEXTURE_SIZE / 2,
                            .y = enemies[i].position.y - ENEMY_TEXTURE_SIZE / 2};
            SDL_BlitSurface(enemyTextures[enemies[i].type], &rect, screen, &pos);
        }
    }
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
            enemies[i].isIced = false;
            return true;
        }
    }
    return false;
}

void damageEnemy(Enemy* enemy, uint16_t damage, bool iced, uint16_t* money)
{
    //TODO: move stat changes somewhere else
    enemy->isIced = iced;

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
        damageEnemy(enemy, damage, iced, money);
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

        uint8_t x = enemies[i].position.x / 16;
        uint8_t y = enemies[i].position.y / 16;

        //Check all directions
        if(enemies[i].toMove <= 0)
        {
            if(tileIsEnd(map, x, y))
            {
                game->lives -= enemies[i].health;
                enemies[i].type = ENT_NONE;
                continue;
            }
            else
            {
                enemies[i].direction = getTileAtPos(map, x, y) - 4;
                //Start tile means move down!
                if(getTileAtPos(map, x, y) == S)
                {
                    enemies[i].direction = 1;
                }
                enemies[i].toMove = 16;
                enemies[i].posDiff = 0;
            }
        }

        enemies[i].toMove -= enemyTypeData[enemies[i].type].speed;
        enemies[i].posDiff += enemyTypeData[enemies[i].type].speed;
        while(enemies[i].posDiff >= 1)
        {
            enemies[i].posDiff -= 1.0f;
            switch(enemies[i].direction)
            {
                case 0:
                {
                    enemies[i].position.y--;
                    break;
                }
                case 1:
                {
                    enemies[i].position.y++;
                    break;
                }
                case 2:
                {
                    enemies[i].position.x--;
                    break;
                }
                case 3:
                {
                    enemies[i].position.x++;
                    break;
                }
            }
        }
    }

    return hasEnemies;
}