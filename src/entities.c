#include "entities.h"

TowerType towerTypes[NUM_TOWER_TYPES] = {
    {.cooldown = 25, .damage = 1, .effect = NONE, .tilePath = "res/towers/Tower_Gun.png"},
    {.cooldown = 50, .damage = 0, .effect = ICE, .tilePath = "res/towers/Tower_ICE.png"}
};

EnemyType enemyTypes[NUM_ENEMY_TYPES] = {
    {.health = 1, .speed = 1, .tilePath = "res/enemies/Enemy_0"}
};

int placeTower(Point* cursor, Tower towers[], TowerType* new)
{
    uint8_t i;
    uint8_t free = 255;
    for(i = 0; i < 225; i++)
    {
        if(!towers[i].type && !free)
        {
            free = i;
        }
        else
        {
            if(towers[i].position.x == cursor->x &&
                towers[i].position.y == cursor->y)
            {
                //Position is already taken
                return 0;
            }
        }
    }

    if(free != 255)
    {
        //We found a spot, place the tower
        towers[i].type = new;
        towers[i].position.x = cursor->x;
        towers[i].position.y = cursor->y;
        return 1;
    }
    return 0;
}

void updateTowers(Tower towers[])
{
    uint8_t i;
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
                towers[i].cooldown = towers[i].type->cooldown;
                //TODO: Fire (check which enemies are in range etc.)
            }
        }
    }
}

void updateEnemies(Enemy enemies[])
{
    //TODO
}