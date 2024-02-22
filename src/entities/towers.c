#include "towers.h"

#include "../effects.h"

//TODO: replace with map tile size?
#define TOWER_TEXTURE_SIZE 16

const TowerTypeData towerTypeData[NUM_TOWER_TYPES] = {
    {.name = "Zap", .attack = A_ZAP,    .cost = 35, .cooldown = 50, .damage = 1, .radius = 2, .texturePath = "res/towers/zap_tower.png", .numFrames = 2},
    {.name = "Ice", .attack = A_ICE,    .cost = 50, .cooldown = 75, .damage = 0, .radius = 2, .texturePath = "res/towers/ice_tower.png", .numFrames = 2},
    {.name = "Fireball", .attack = A_FIRE,   .cost = 70, .cooldown = 20, .damage = 1, .radius = 3, .texturePath = "res/towers/fire_tower.png", .numFrames = 2},
    {.name = "Cannon", .attack = A_CANNON, .cost = 55, .cooldown = 60, .damage = 8, .radius = 4, .texturePath = "res/towers/cannon_tower.png", .numFrames = 2}
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
    //TODO
    int animCounter = 0;

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

void updateTowers(Tower* towers, uint16_t maxTowers, Enemy* enemies, uint16_t maxEnemies, Projectile projectiles[], uint16_t* money)
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
        
        uint8_t radius = towerTypeData[towers[i].type].radius;
        uint16_t damage = towerTypeData[towers[i].type].damage;
        uint8_t displayEffect = 1;

        //TODO: Fire on enemies in order (at first enemy in range!) -> maybe with an enemy index as attribute?
        for(uint16_t j = 0; j < maxEnemies; j++)
        {
            if(enemies[j].type != ENT_NONE)
            {
                if(vec2i_distance(&enemies[j].position, &towers[i].position) <= radius)
                {
                    const TowerTypeData* type = &towerTypeData[towers[i].type];

                    towers[i].cooldown = type->cooldown;
                    
                    if(type->attack == A_ZAP)
                    {
                        damageEnemy(&enemies[j], damage, 0, money);
                        addEffect(EFT_ZAP, towers[i].position.x * 16 + 8, towers[i].position.y * 16 + 8, &enemies[j].position, type->radius);
                        //ZAP can only fire at one enemy, we're done
                        break;
                    }
                    else if(type->attack == A_ICE)
                    {
                        //TODO: Slow the enemy down instead of damaging it - or maybe both?
                        damageEnemy(&enemies[j], damage, 1, money);
                        if(displayEffect)
                        {
                            addEffect(EFT_ICE, towers[i].position.x * 16 + 8, towers[i].position.y * 16 + 8, &enemies[j].position, type->radius);
                            //Keep going, but don't add multiple effects
                            displayEffect = 0;
                        }
                    }
                    else if(type->attack == A_FIRE)
                    {
                        addProjectile(projectiles, towers[i].position.x, towers[i].position.y, enemies[j].position.x, enemies[j].position.y, 0);
                        break;
                    }
                    else if(type->attack == A_CANNON)
                    {
                        addProjectile(projectiles, towers[i].position.x, towers[i].position.y, enemies[j].position.x, enemies[j].position.y, 1);
                        break;
                    }
                }
            }
        }
    }
}
