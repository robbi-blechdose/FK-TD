#include "projectiles.h"

#include "../effects.h"

const ProjectileTypeData projectileTypes[NUM_PROJECTILE_TYPES] = {
    {.life =  5, .damage = 1, .radius =  8, .hitEffect = EFT_NONE,      .tilePath = "res/projectiles/fireball.png"},
    {.life = 10, .damage = 2, .radius = 16, .hitEffect = EFT_EXPLOSION, .tilePath = "res/projectiles/cannonball.png"}
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

void drawProjectiles(SDL_Surface* screen, Projectile projectiles[])
{
    //TODO
    int animCounter = 0;

    for(uint8_t i = 0; i < 225; i++)
    {
        if(projectiles[i].type != PT_NONE)
        {
            SDL_Rect rect = {.x = (animCounter / 8 % 2) * 8, .y = 0, .w = 8, .h = 8};
            SDL_Rect pos = {.x = projectiles[i].position.x, .y = projectiles[i].position.y};
            SDL_BlitSurface(projectileTextures[projectiles[i].type], &rect, screen, &pos);
        }
    }
}

bool addProjectile(Projectile projectiles[], uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, uint8_t type)
{
    for(uint8_t i = 0; i < 255; i++)
    {
        if(projectiles[i].type == PT_NONE)
        {
            projectiles[i].type = type;
            projectiles[i].timer = projectileTypes[type].life;
            projectiles[i].source.x = x * 16 + 8;
            projectiles[i].source.y = y * 16 + 8;
            projectiles[i].position.x = x * 16 + 8;
            projectiles[i].position.y = y * 16 + 8;
            projectiles[i].target.x = tx + 8;
            projectiles[i].target.y = ty + 8;

            return true;
        }
    }
    return false;
}

bool updateProjectiles(Projectile projectiles[], Enemy enemies[], uint16_t* money)
{
    bool hasProjectiles = false;

    for(uint8_t i = 0; i < 225; i++)
    {
        if(projectiles[i].type == PT_NONE)
        {
            continue;
        }

        hasProjectiles = true;

        projectiles[i].position.x = lerp(projectiles[i].target.x, projectiles[i].source.x, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
        projectiles[i].position.y = lerp(projectiles[i].target.y, projectiles[i].source.y, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
        projectiles[i].timer--;
        if(!projectiles[i].timer)
        {
            projectiles[i].type = PT_NONE;
        }

        for(uint8_t j = 0; j < 225; j++)
        {
            if(vec2i_withinRadius(&enemies[j].position, &projectiles[i].position, projectileTypes[projectiles[i].type].radius))
            {
                if(projectileTypes[projectiles[i].type].hitEffect != EFT_NONE)
                {
                    vec2i zero = {0, 0};
                    addEffect(projectileTypes[projectiles[i].type].hitEffect, projectiles[i].position.x, projectiles[i].position.y, &zero, 0);
                }
                damageEnemy(&enemies[j], projectileTypes[projectiles[i].type].damage, 0, money);
                projectiles[i].type = PT_NONE;
            }
        }
    }

    return hasProjectiles;
}