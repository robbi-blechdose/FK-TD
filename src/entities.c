#include "entities.h"

//Fixed data
const TowerType towerTypes[NUM_TOWER_TYPES] = {
    {.attack = A_ZAP,    .cost = 35, .cooldown = 50, .damage = 1, .radius = 2, .tilePath = "res/towers/zap_tower.png", .frames = 2},
    {.attack = A_ICE,    .cost = 50, .cooldown = 75, .damage = 0, .radius = 2, .tilePath = "res/towers/ice_tower.png", .frames = 2},
    {.attack = A_FIRE,   .cost = 70, .cooldown = 20, .damage = 1, .radius = 3, .tilePath = "res/towers/fire_tower.png", .frames = 2},
    {.attack = A_CANNON, .cost = 55, .cooldown = 60, .damage = 8, .radius = 4, .tilePath = "res/towers/cannon_tower.png", .frames = 2}
};

const EnemyType enemyTypes[NUM_ENEMY_TYPES] = {
    {.health = 1, .speed = 0.8f, .tilePath = "res/enemies/Enemy_0.png", .contains = ENEMY_TYPE_NONE},
    {.health = 2, .speed = 1.0f, .tilePath = "res/enemies/Enemy_1.png", .contains = 0},
    {.health = 3, .speed = 1.2f, .tilePath = "res/enemies/Enemy_2.png", .contains = 1},
    {.health = 4, .speed = 1.5f, .tilePath = "res/enemies/Enemy_3.png", .contains = 2},
    {.health = 5, .speed = 2.0f, .tilePath = "res/enemies/Enemy_4.png", .contains = 3},
    {.health = 6, .speed = 2.5f, .tilePath = "res/enemies/Enemy_5.png", .contains = 4}
};

const ProjectileType projectileTypes[NUM_PROJECTILE_TYPES] = {
    {.life =  5, .damage = 1, .radius =  8, .hitEffect = E_NONE,      .tilePath = "res/projectiles/fireball.png"},
    {.life = 10, .damage = 2, .radius = 16, .hitEffect = E_EXPLOSION, .tilePath = "res/projectiles/cannonball.png"}
};

//Graphics
SDL_Surface* towerTiles[NUM_TOWER_TYPES];
SDL_Surface* enemyTiles[NUM_ENEMY_TYPES];
SDL_Surface* projectileTiles[NUM_PROJECTILE_TYPES];

bool placeTower(Point* cursor, Tower towers[], uint8_t type, Map* map)
{
    uint8_t free = 255;

    if(tileIsReserved(map, cursor->x, cursor->y))
    {
        //Can't place here
        return false;
    }
    
    for(uint8_t i = 0; i < 225; i++)
    {
        if(towers[i].type != TOWER_TYPE_NONE)
        {
            if(towers[i].position.x == cursor->x &&
                towers[i].position.y == cursor->y)
            {
                //Position is already taken
                return false;
            }
        }
        else if(free == 255)
        {
            free = i;
        }
    }

    if(free != 255)
    {
        //We found a spot, place the tower
        towers[free].type = type;
        towers[free].position.x = cursor->x;
        towers[free].position.y = cursor->y;
        return true;
    }
    return false;
}

bool addEnemy(Enemy enemies[], uint8_t x, uint8_t y, uint8_t dir, uint8_t type)
{
    for(uint8_t i = 0; i < 225; i++)
    {
        if(enemies[i].type == ENEMY_TYPE_NONE)
        {
            //We found a free spot, insert the enemy
            enemies[i].type = type;
            enemies[i].position.x = x;
            enemies[i].position.y = y;
            enemies[i].direction = dir;
            enemies[i].toMove = 0;
            enemies[i].health = enemyTypes[type].health;
            enemies[i].isIced = 0;
            return true;
        }
    }
    return false;
}

bool addProjectile(Projectile projectiles[], uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, uint8_t type)
{
    for(uint8_t i = 0; i < 255; i++)
    {
        if(projectiles[i].type == PROJECTILE_TYPE_NONE)
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

void damageEnemy(Enemy enemies[], Enemy* e, uint16_t damage, uint8_t iced, uint16_t* money)
{
    if(e->health > damage)
    {
        e->type = enemyTypes[e->type].contains;
        e->health = enemyTypes[e->type].health;
        e->isIced = iced;
        if(damage - 1 > 0)
        {
            damageEnemy(enemies, e, damage - 1, iced, money);
        }

    }
    else
    {
        e->type = ENEMY_TYPE_NONE;
    }
    (*money)++;
}

void updateTowers(Tower towers[], Enemy enemies[], Projectile projectiles[], uint16_t* money)
{
    for(uint8_t i = 0; i < 225; i++)
    {
        if(towers[i].type != TOWER_TYPE_NONE)
        {
            if(towers[i].cooldown > 0)
            {
                towers[i].cooldown--;
                continue;
            }
            
            uint8_t radius = towerTypes[towers[i].type].radius;
            uint16_t damage = towerTypes[towers[i].type].damage;
            uint8_t displayEffect = 1;

            //TODO: Fire on enemies in order (at first enemy in range!) -> maybe with an enemy index as attribute?
            for(uint8_t j = 0; j < 225; j++)
            {
                if(enemies[j].type != ENEMY_TYPE_NONE)
                {
                    if(distanceTE(&enemies[j].position, &towers[i].position) <= radius)
                    {
                        const TowerType* type = &towerTypes[towers[i].type];

                        towers[i].cooldown = type->cooldown;
                        
                        if(type->attack == A_ZAP)
                        {
                            damageEnemy(enemies, &enemies[j], damage, 0, money);
                            addEffect(E_ZAP, towers[i].position.x * 16 + 8, towers[i].position.y * 16 + 8, &enemies[j].position, type->radius);
                            //ZAP can only fire at one enemy, we're done
                            break;
                        }
                        else if(type->attack == A_ICE)
                        {
                            //TODO: Slow the enemy down instead of damaging it - or maybe both?
                            damageEnemy(enemies, &enemies[j], damage, 1, money);
                            if(displayEffect)
                            {
                                addEffect(E_ICE, towers[i].position.x * 16 + 8, towers[i].position.y * 16 + 8, &enemies[j].position, type->radius);
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
}

bool updateEnemies(Enemy enemies[], Map* map, Game* game)
{
    bool hasEnemies = false;

    for(uint8_t i = 0; i < 225; i++)
    {
        if(enemies[i].type != ENEMY_TYPE_NONE)
        {
            hasEnemies = true;

            uint8_t x = enemies[i].position.x / 16;
            uint8_t y = enemies[i].position.y / 16;

            //Check all directions
            if(enemies[i].toMove <= 0)
            {
                if(tileIsEnd(map, x, y))
                {
                    game->lives -= enemies[i].health;
                    enemies[i].type = ENEMY_TYPE_NONE;
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

            enemies[i].toMove -= enemyTypes[enemies[i].type].speed;
            enemies[i].posDiff += enemyTypes[enemies[i].type].speed;
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
    }

    return hasEnemies;
}

bool updateProjectiles(Projectile projectiles[], Enemy enemies[], uint16_t* money)
{
    bool hasProjectiles = false;

    for(uint8_t i = 0; i < 225; i++)
    {
        if(projectiles[i].type != PROJECTILE_TYPE_NONE)
        {
            hasProjectiles = true;

            projectiles[i].position.x = lerp(projectiles[i].target.x, projectiles[i].source.x, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
            projectiles[i].position.y = lerp(projectiles[i].target.y, projectiles[i].source.y, projectiles[i].timer / (float) projectileTypes[projectiles[i].type].life);
            projectiles[i].timer--;
            if(!projectiles[i].timer)
            {
                projectiles[i].type = PROJECTILE_TYPE_NONE;
            }

            for(uint8_t j = 0; j < 225; j++)
            {
                if(hitPE(&enemies[j].position, &projectiles[i].position, projectileTypes[projectiles[i].type].radius))
                {
                    if(projectileTypes[projectiles[i].type].hitEffect != E_NONE)
                    {
                        Point zero = {0, 0};
                        addEffect(projectileTypes[projectiles[i].type].hitEffect, projectiles[i].position.x, projectiles[i].position.y, &zero, 0);
                    }
                    damageEnemy(enemies, &enemies[j], projectileTypes[projectiles[i].type].damage, 0, money);
                    projectiles[i].type = PROJECTILE_TYPE_NONE;
                }
            }
        }
    }

    return hasProjectiles;
}