#include <stdlib.h>
#include "wavegenerator.h"

uint16_t timer;
uint16_t rcount;
uint16_t rushActive;
vec2i startPoint;

void initWaveGenerator(uint8_t wave, vec2i sp)
{
    rcount = 12 * wave;
    rushActive = 0;
    startPoint.x = sp.x * 16;
    startPoint.y = sp.y * 16;
}

void spawnEnemy(Enemy* enemies, uint16_t maxEnemies, uint8_t wave)
{
    uint8_t enemyIndex = (rand() % (wave * 100)) / 100;
    if(enemyIndex > 5)
    {
        enemyIndex = 5;
    }
    addEnemy(enemies, maxEnemies, startPoint.x, startPoint.y, 1, enemyIndex);
    rcount--;
}

bool updateWaveGenerator(Enemy* enemies, uint16_t maxEnemies, uint8_t wave)
{
    if(rcount == 0)
    {
        return false;
    }

    if(!rushActive && rand() < RAND_MAX / 500)
    {
        rushActive = rand() % rcount;
        if(rushActive > 8)
        {
            rushActive = 8;
        }
        timer = 0;
    }

    timer++;
    
    if(rushActive)
    {
        if(timer == 10)
        {
            timer = 0;
            rushActive--;
            spawnEnemy(enemies, maxEnemies, wave);
        }
    }
    else
    {
        if(timer == 24)
        {
            timer = 0;
            spawnEnemy(enemies, maxEnemies, wave);
        }
    }
    return true;
}