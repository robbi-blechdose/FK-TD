#include "towers.h"

#include "../effects.h"

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
void drawTowers(SDL_Surface* screen, Tower* towers, uint16_t maxTowers)
{
    static uint8_t animCounter = 0;
    animCounter++;

    for(uint16_t i = 0; i < maxTowers; i++)
    {
        if(towers[i].type != TT_NONE)
        {
            SDL_Rect pos = {.x = towers[i].position.x * TOWER_TEXTURE_SIZE,
                            .y = towers[i].position.y * TOWER_TEXTURE_SIZE};
            if(towerTypeData[towers[i].type].numFrames)
            {
                SDL_Rect rect = {.x = (animCounter / TOWER_TEXTURE_SIZE % towerTypeData[towers[i].type].numFrames) * TOWER_TEXTURE_SIZE,
                                    .y = 0, .w = TOWER_TEXTURE_SIZE, .h = TOWER_TEXTURE_SIZE};
                SDL_BlitSurface(towerTextures[towers[i].type], &rect, screen, &pos);
            }
            else
            {
                SDL_BlitSurface(towerTextures[towers[i].type], NULL, screen, &pos);
            }
        }
    }
}

bool placeTower(vec2i* cursor, Tower* towers, uint16_t maxTowers, uint8_t type, Map* map)
{
    if(tileIsReserved(map, cursor->x, cursor->y))
    {
        //Can't place here
        return false;
    }

    bool hasFreeIndex = false;
    uint16_t freeIndex = 0;
    
    //Find the first free index AND check all tower positions to make sure there's no tower in the same position
    for(uint16_t i = 0; i < maxTowers; i++)
    {
        if(towers[i].type != TT_NONE)
        {
            if(towers[i].position.x == cursor->x &&
                towers[i].position.y == cursor->y)
            {
                //Position is already taken
                return false;
            }
        }
        else if(!hasFreeIndex)
        {
            hasFreeIndex = true;
            freeIndex = i;
        }
    }

    if(hasFreeIndex)
    {
        //We found a spot, place the tower
        towers[freeIndex].type = type;
        towers[freeIndex].position.x = cursor->x;
        towers[freeIndex].position.y = cursor->y;
        return true;
    }
    return false;
}

void towerAttack(Tower* tower, Enemy* enemies, uint16_t maxEnemies, Projectile* projectiles, uint16_t maxProjectiles, uint16_t* money)
{
    uint8_t radius = towerTypeData[tower->type].radius;
    bool displayEffect = true;

    //TODO: Fire on enemies in order (at first enemy in range!) -> maybe with an enemy index as attribute?
    for(uint16_t j = 0; j < maxEnemies; j++)
    {
        if(enemies[j].type == ENT_NONE)
        {
            continue;
        }

        vec2i enemyPosition = (vec2i) {.x = enemies[j].position.x, .y = enemies[j].position.y};
        if(vec2i_distance(&enemyPosition, &tower->position) > radius)
        {
            continue;
        }

        uint16_t damage = towerTypeData[tower->type].damage;
        tower->cooldown = towerTypeData[tower->type].cooldown;

        vec2 towerCenter = (vec2) {.x = tower->position.x + 0.5f, .y = tower->position.y + 0.5f};
        vec2 enemyCenter = (vec2) {.x = enemies[j].position.x + 0.5f, .y = enemies[j].position.y + 0.5f};
        
        if(tower->type == TT_ZAP)
        {
            damageEnemy(&enemies[j], damage, money);
            addEffect(EFT_ZAP, towerCenter, enemyCenter, towerTypeData[tower->type].radius);
            //ZAP can only fire at one enemy, we're done
            break;
        }
        else if(tower->type == TT_ICE)
        {
            damageEnemy(&enemies[j], damage, money);
            addStatToEnemy(&enemies[j], STAT_ICED);
            if(displayEffect)
            {
                addEffect(EFT_ICE, towerCenter, enemyCenter, towerTypeData[tower->type].radius);
                //Keep going, but don't add multiple effects
                displayEffect = false;
            }
        }
        else if(tower->type == TT_FIREBALL)
        {
            addProjectile(projectiles, maxProjectiles, towerCenter, enemyCenter, PT_FIREBALL);
            break;
        }
        else if(tower->type == TT_CANNON)
        {
            addProjectile(projectiles, maxProjectiles, towerCenter, enemyCenter, PT_CANNONBALL);
            break;
        }
    }
}

void updateTowers(Tower* towers, uint16_t maxTowers, Enemy* enemies, uint16_t maxEnemies, Projectile* projectiles, uint16_t maxProjectiles, uint16_t* money)
{
    for(uint16_t i = 0; i < maxTowers; i++)
    {
        if(towers[i].type == TT_NONE)
        {
            continue;
        }

        if(towers[i].cooldown > 0)
        {
            towers[i].cooldown--;
            continue;
        }
        
        towerAttack(&towers[i], enemies, maxEnemies, projectiles, maxProjectiles, money);
    }
}
