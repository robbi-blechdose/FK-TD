#include <stdlib.h>
#include "wavegenerator.h"

uint16_t timer;
uint16_t rcount;
uint16_t rushActive;

void initWaveGenerator(uint8_t wave)
{
    rcount = 12 * wave;
    rushActive = 0;
}

void spawnEnemy(Enemy enemies[], uint8_t wave)
{
    uint8_t enemyIndex = (rand() % (wave * 100)) / 100;
    addEnemy(enemies, 16, 16, 1, &enemyTypes[enemyIndex]);
    rcount--;
}

uint8_t updateWaveGenerator(Enemy enemies[], uint8_t wave)
{
    if(rcount == 0)
    {
        return 0;
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
            spawnEnemy(enemies, wave);
        }
    }
    else
    {
        if(timer == 24)
        {
            timer = 0;
            spawnEnemy(enemies, wave);
        }
    }
    return 1;
}