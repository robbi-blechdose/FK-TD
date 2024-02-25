#include "towers.h"

#include "../effects.h"
//TODO: move map size and map tile size somewhere else so we don't need to include the map header?
#include "../map.h"

//TODO: replace with map tile size?
#define TOWER_TEXTURE_SIZE 16

const TowerTypeData towerTypeData[NUM_TOWER_TYPES] = {
    {.name = "Zap",      .cost = 35, .cooldown = 50, .damage = 1, .radius = 2, .texturePath = "res/towers/zap_tower.png", .numFrames = 2},
    {.name = "Ice",      .cost = 50, .cooldown = 75, .damage = 0, .radius = 2, .texturePath = "res/towers/ice_tower.png", .numFrames = 2},
    {.name = "Fireball", .cost = 70, .cooldown = 20, .damage = 1, .radius = 3, .texturePath = "res/towers/fire_tower.png", .numFrames = 2},
    {.name = "Cannon",   .cost = 55, .cooldown = 60, .damage = 8, .radius = 4, .texturePath = "res/towers/cannon_tower.png", .numFrames = 2}
};

SDL_Surface* towerTextures[NUM_TOWER_TYPES];

void initTowers()
{
    for(uint8_t i = 0; i < NUM_TOWER_TYPES; i++)
    {
        towerTextures[i] = loadPNG(towerTypeData[i].texturePath);
    }
}

void quitTowers()
{
    //TODO
}

void drawTower(SDL_Surface* screen, TowerType tower, vec2i position)
{
    SDL_Rect pos = {.x = position.x, .y = position.y};
    SDL_Rect rect = {.x = 0, .y = 0, .w = TOWER_TEXTURE_SIZE, .h = TOWER_TEXTURE_SIZE};
    SDL_BlitSurface(towerTextures[tower], &rect, screen, &pos);
}

void drawTowerWithRange(SDL_Surface* screen, TowerType tower, vec2i position)
{
    drawTower(screen, tower, position);
    circleRGBA(screen, position.x + TOWER_TEXTURE_SIZE / 2,
                        position.y + TOWER_TEXTURE_SIZE / 2,
                        towerTypeData[tower].radius * 16, 255, 255, 255, 255); //TODO: replace 16 with map tile size constant
}

//TODO: switch to using drawTower
void drawTowers(SDL_Surface* screen, Tower* towers)
{
    static uint8_t animCounter = 0;
    animCounter++;

    for(uint16_t i = 0; i < MAP_WIDTH; i++)
    {
        for(uint16_t j = 0; j < MAP_HEIGHT; j++)
        {
            Tower* tower = &towers[i + j * MAP_WIDTH];

            if(tower->type != TT_NONE)
            {
                SDL_Rect pos = {.x = i * TOWER_TEXTURE_SIZE,
                                .y = j * TOWER_TEXTURE_SIZE};
                
                if(towerTypeData[tower->type].numFrames)
                {
                    SDL_Rect rect = {.x = (animCounter / TOWER_TEXTURE_SIZE % towerTypeData[tower->type].numFrames) * TOWER_TEXTURE_SIZE,
                                        .y = 0,
                                        .w = TOWER_TEXTURE_SIZE,
                                        .h = TOWER_TEXTURE_SIZE};
                    SDL_BlitSurface(towerTextures[tower->type], &rect, screen, &pos);
                }
                else
                {
                    SDL_BlitSurface(towerTextures[tower->type], NULL, screen, &pos);
                }
            }
        }
    }
}

bool placeTower(vec2i* cursor, Tower* towers, uint8_t type, const Map* map)
{
    if(tileIsReserved(map, cursor->x, cursor->y))
    {
        return false;
    }
    
    if(towers[cursor->x + cursor->y * MAP_WIDTH].type != TT_NONE)
    {
        return false;
    }

    towers[cursor->x + cursor->y * MAP_WIDTH].type = type;
    return true;
}

Enemy* getFirstEnemy(Enemy* enemies, uint16_t maxEnemies, vec2 towerCenter, float towerRadius)
{
    uint16_t index = 0;
    float maxTotalDistance = 0;

    for(uint16_t i = 0; i < maxEnemies; i++)
    {
        if(enemies[i].type == ENT_NONE)
        {
            continue;
        }

        vec2 enemyCenter = (vec2) {.x = enemies[i].position.x + 0.5f, .y = enemies[i].position.y + 0.5f};
        if(vec2_distance(enemyCenter, towerCenter) > towerRadius)
        {
            continue;
        }

        if(enemies[i].totalDistance > maxTotalDistance)
        {
            maxTotalDistance = enemies[i].totalDistance;
            index = i;
        }
    }

    if(maxTotalDistance > 0)
    {
        return &enemies[index];
    }
    return NULL;
}

void towerAttack(Tower* tower, vec2 towerCenter, Enemy* enemies, uint16_t maxEnemies, Projectile* projectiles, uint16_t maxProjectiles, uint16_t* money)
{
    bool fired = false;
    
    switch(tower->type)
    {
        case TT_ZAP:
        {
            Enemy* firstEnemy = getFirstEnemy(enemies, maxEnemies, towerCenter, towerTypeData[tower->type].radius);

            if(firstEnemy != NULL)
            {
                vec2 enemyCenter = (vec2) {.x = firstEnemy->position.x + 0.5f, .y = firstEnemy->position.y + 0.5f};
                damageEnemy(firstEnemy, towerTypeData[tower->type].damage, money);
                addEffect(EFT_ZAP, towerCenter, enemyCenter, towerTypeData[tower->type].radius);
                fired = true;
            }
            break;
        }
        case TT_ICE:
        {
            for(uint16_t i = 0; i < maxEnemies; i++)
            {
                if(enemies[i].type == ENT_NONE)
                {
                    continue;
                }

                vec2 enemyCenter = (vec2) {.x = enemies[i].position.x + 0.5f, .y = enemies[i].position.y + 0.5f};
                if(vec2_distance(enemyCenter, towerCenter) > towerTypeData[tower->type].radius)
                {
                    continue;
                }

                damageEnemy(&enemies[i], towerTypeData[tower->type].damage, money);
                addStatToEnemy(&enemies[i], STAT_ICED);
                if(!fired)
                {
                    addEffect(EFT_ICE, towerCenter, enemyCenter, towerTypeData[tower->type].radius);
                    //Keep going, but don't add multiple effects
                    fired = true;
                }
            }
            break;
        }
        case TT_FIREBALL:
        {
            Enemy* firstEnemy = getFirstEnemy(enemies, maxEnemies, towerCenter, towerTypeData[tower->type].radius);

            if(firstEnemy != NULL)
            {
                vec2 enemyCenter = (vec2) {.x = firstEnemy->position.x + 0.5f, .y = firstEnemy->position.y + 0.5f};
                addProjectile(projectiles, maxProjectiles, towerCenter, enemyCenter, PT_FIREBALL);
                fired = true;
            }
            break;
        }
        case TT_CANNON:
        {
            Enemy* firstEnemy = getFirstEnemy(enemies, maxEnemies, towerCenter, towerTypeData[tower->type].radius);

            if(firstEnemy != NULL)
            {
                vec2 enemyCenter = (vec2) {.x = firstEnemy->position.x + 0.5f, .y = firstEnemy->position.y + 0.5f};
                addProjectile(projectiles, maxProjectiles, towerCenter, enemyCenter, PT_CANNONBALL);
                fired = true;
            }
            break;
        }
    }

    if(fired)
    {
        tower->cooldown = towerTypeData[tower->type].cooldown;
    }
}

void updateTowers(Tower* towers, Enemy* enemies, uint16_t maxEnemies, Projectile* projectiles, uint16_t maxProjectiles, uint16_t* money)
{
    for(uint16_t i = 0; i < MAP_WIDTH; i++)
    {
        for(uint16_t j = 0; j < MAP_HEIGHT; j++)
        {
            Tower* tower = &towers[i + j * MAP_WIDTH];

            if(tower->type == TT_NONE)
            {
                continue;
            }

            if(tower->cooldown > 0)
            {
                tower->cooldown--;
                continue;
            }
            
            vec2 towerCenter = (vec2) {.x = i + 0.5f, .y = j + 0.5f};
            towerAttack(tower, towerCenter, enemies, maxEnemies, projectiles, maxProjectiles, money);
        }
    }
}
