#include "projectiles.h"

#include "../effects.h"

const ProjectileTypeData projectileTypes[NUM_PROJECTILE_TYPES] = {
    {.life =  5, .damage = 1, .radius = 0.5f, .hitEffect = EFT_NONE,      .tilePath = "res/projectiles/fireball.png"},
    {.life = 10, .damage = 2, .radius = 1.0f, .hitEffect = EFT_EXPLOSION, .tilePath = "res/projectiles/cannonball.png"}
};

SDL_Surface* projectileTextures[NUM_PROJECTILE_TYPES];

void initProjectiles()
{
    for(uint8_t i = 0; i < NUM_PROJECTILE_TYPES; i++)
    {
        projectileTextures[i] = loadPNG(projectileTypes[i].tilePath);
    }
}

void quitProjectiles()
{
    //TODO
}

void drawProjectiles(SDL_Surface* screen, Projectile* projectiles, uint16_t maxProjectiles)
{
    static uint8_t animCounter = 0;
    animCounter++;

    for(uint16_t i = 0; i < maxProjectiles; i++)
    {
        if(projectiles[i].type != PT_NONE)
        {
            SDL_Rect rect = {.x = (animCounter / 8 % 2) * 8,
                                .y = 0,
                                .w = 8, .h = 8};
            SDL_Rect pos = {.x = projectiles[i].position.x * 16 - 4,
                            .y = projectiles[i].position.y * 16 - 4};
            SDL_BlitSurface(projectileTextures[projectiles[i].type], &rect, screen, &pos);
        }
    }
}

bool addProjectile(Projectile* projectiles, uint16_t maxProjectiles, vec2 sourcePos, vec2 targetPos, ProjectileType type)
{
    for(uint16_t i = 0; i < maxProjectiles; i++)
    {
        if(projectiles[i].type == PT_NONE)
        {
            projectiles[i].type = type;
            projectiles[i].timer = projectileTypes[type].life;
            projectiles[i].source.x = sourcePos.x;
            projectiles[i].source.y = sourcePos.y;
            projectiles[i].position.x = sourcePos.x;
            projectiles[i].position.y = sourcePos.y;
            projectiles[i].target.x = targetPos.x;
            projectiles[i].target.y = targetPos.y;
            return true;
        }
    }
    return false;
}

bool updateProjectiles(Projectile* projectiles, uint16_t maxProjectiles, Enemy* enemies, uint16_t maxEnemies, uint16_t* money)
{
    bool hasProjectiles = false;

    for(uint16_t i = 0; i < maxProjectiles; i++)
    {
        if(projectiles[i].type == PT_NONE)
        {
            continue;
        }

        hasProjectiles = true;

        projectiles[i].position.x = lerpf(projectiles[i].target.x, projectiles[i].source.x, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
        projectiles[i].position.y = lerpf(projectiles[i].target.y, projectiles[i].source.y, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
        projectiles[i].timer--;

        bool hit = false;
        for(uint16_t j = 0; j < maxEnemies; j++)
        {
            if(enemies[j].type == ENT_NONE)
            {
                continue;
            }

            vec2 enemyCenter = (vec2) {.x = enemies[j].position.x + 0.5f, .y = enemies[j].position.y + 0.5f};
            if(vec2_withinRadius(enemyCenter, projectiles[i].position, projectileTypes[projectiles[i].type].radius))
            {
                if(projectileTypes[projectiles[i].type].hitEffect != EFT_NONE)
                {
                    addEffect(projectileTypes[projectiles[i].type].hitEffect, projectiles[i].position, (vec2) {0, 0}, 0);
                }
                damageEnemy(&enemies[j], projectileTypes[projectiles[i].type].damage, money);
                hit = true;
            }
        }
        if(hit || !projectiles[i].timer)
        {
            projectiles[i].type = PT_NONE;
        }
    }

    return hasProjectiles;
}