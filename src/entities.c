#include "entities.h"
#include "effects.h"

TowerType towerTypes[NUM_TOWER_TYPES] = {
    {.cost = 50, .cooldown = 50, .damage = 1, .radius = 2, .tilePath = "res/towers/Tower_Zap.png"},
    {.cost = 100, .cooldown = 50, .damage = 0, .radius = 2, .tilePath = "res/towers/Tower_Ice.png"}
};

EnemyType enemyTypes[NUM_ENEMY_TYPES] = {
    {.health = 1, .speed = 1, .tilePath = "res/enemies/Enemy_0.png"}
};

int placeTower(Point* cursor, Tower towers[], TowerType* new)
{
    uint8_t i;
    uint8_t free = 255;
    for(i = 0; i < 225; i++)
    {
        if(towers[i].type)
        {
            if(towers[i].position.x == cursor->x &&
                towers[i].position.y == cursor->y)
            {
                //Position is already taken
                return 0;
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
        towers[free].type = new;
        towers[free].position.x = cursor->x;
        towers[free].position.y = cursor->y;
        return 1;
    }
    return 0;
}

int addEnemy(Enemy enemies[], uint8_t x, uint8_t y, uint8_t dir, EnemyType* new)
{
    uint8_t i;
    uint8_t free = 255;
    for(i = 0; i < 225; i++)
    {
        if(!enemies[i].type)
        {
            free = i;
            break;
        }
    }

    if(free != 255)
    {
        //We found a spot, place the tower
        enemies[free].type = new;
        enemies[free].position.x = x;
        enemies[free].position.y = y;
        enemies[free].direction = dir;
        enemies[free].health = new->health;
        return 1;
    }
    return 0;
}

void updateTowers(Tower towers[], Enemy enemies[])
{
    uint8_t i, j;
    for(i = 0; i < 225; i++)
    {
        if(towers[i].type)
        {
            if(towers[i].cooldown > 0)
            {
                towers[i].cooldown--;
            }
            else
            {
                uint8_t radius = towers[i].type->radius;
                uint16_t damage = towers[i].type->damage;

                for(j = 0; j < 225; j++)
                {
                    if(enemies[j].type)
                    {
                        if(distanceTE(&enemies[j].position, &towers[i].position) <= radius)
                        {
                            addEffect(ZAP, &towers[i].position, &enemies[j].position);
                            enemies[j].health -= damage;
                            towers[i].cooldown = towers[i].type->cooldown;
                            break;
                        }
                    }
                }
            }
        }
    }
}

uint8_t updateEnemies(Enemy enemies[], Map* map, uint8_t* lives)
{
    uint8_t i;
    uint8_t hasEnemies = 0;
    for(i = 0; i < 225; i++)
    {
        if(enemies[i].type)
        {
            hasEnemies = 1;

            uint8_t dir = enemies[i].direction;
            uint8_t x = enemies[i].position.x / 16;
            uint8_t y = enemies[i].position.y / 16;

            //TODO: Check and fix pathfinding bug
            //Check health
            if(!enemies[i].health)
            {
                enemies[i].type = NULL;
                continue;
            }

            //Check all directions
            if(!enemies[i].toMove)
            {
                if(tileIsEnd(map, x, y))
                {
                    (*lives)--;
                    enemies[i].type = NULL;
                    continue;
                }
                else if(tileIsPath(map, x, y - 1) && dir != 1)
                {
                    enemies[i].direction = 0;
                    enemies[i].toMove = 16;
                }
                else if(tileIsPath(map, x, y + 1) && dir != 0)
                {
                    enemies[i].direction = 1;
                    enemies[i].toMove = 16;
                }
                else if(tileIsPath(map, x - 1, y) && dir != 3)
                {
                    enemies[i].direction = 2;
                    enemies[i].toMove = 16;
                }
                else if(tileIsPath(map, x + 1, y) && dir != 2)
                {
                    enemies[i].direction = 3;
                    enemies[i].toMove = 16;
                }
            }

            enemies[i].toMove -= enemies[i].type->speed;
            switch(enemies[i].direction)
            {
                case 0:
                {
                    enemies[i].position.y -= enemies[i].type->speed;
                    break;
                }
                case 1:
                {
                    enemies[i].position.y += enemies[i].type->speed;
                    break;
                }
                case 2:
                {
                    enemies[i].position.x -= enemies[i].type->speed;
                    break;
                }
                case 3:
                {
                    enemies[i].position.x += enemies[i].type->speed;
                    break;
                }
            }
        }
    }

    return hasEnemies;
}